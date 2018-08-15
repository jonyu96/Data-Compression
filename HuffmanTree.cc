//
//  HuffmanTree.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/6/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#include "HuffmanTree.h"

using namespace std;

HuffmanTree::HuffmanTree(const FrequencyTable& freqTable) : root(nullptr) {
    
    Heap<Node<unsigned char, unsigned int>*,
    std::vector<Node<unsigned char, unsigned int>*>,
    Compare<unsigned char, unsigned int>> priorityQueue;
    
    // builds priority queue based on frequencies of characters
    for (int i = 0; i < UCHAR_MAX + 1; i++) {
        
        unsigned char c = static_cast<unsigned char>(i);
        
        if (freqTable.get(c) > 0) {
            Node<unsigned char, unsigned int>* temp =
            new Node<unsigned char, unsigned int>(c, freqTable.get(i));
            
            priorityQueue.push(temp);
        }
    }
    
    cerr << "Checking priority queue before building Huffman Tree...\n\n";
    priorityQueue.verify(); // verify priority queue
    
    // build tree from priority queue
    root = buildTree(priorityQueue);
}

HuffmanTree::HuffmanTree(BitInputStream& bitIn, CodeTable& table,
                         unsigned int& totalCount) {
    
    root = new Node<unsigned char, unsigned int>();
    
    cerr << "\nReading code table header from encoded file..\n\n" << endl;
    cerr << "HEX\t\tCharacter\tCode Length\t\tCode Pattern" << endl;
    cerr << "----------------------------------";
    cerr << "----------------------------------" << endl;
    
    for (int i = 0; i < UCHAR_MAX + 1; i++) {
        char c = i;
        cerr << showbase << hex << static_cast<int>(i) << dec;
        cerr << "\t\t(" << (isprint(c) ? c : ' ') << ")";
        cerr << "\t\t";
        
        int bitLength = bitIn.getByte(); // read in length as byte
        unsigned long long bitCode = 0;

        if (bitLength > 0) {
            cerr << "\t\t[";
            
            // read in code pattern bit by bit
            for (int i = 0; i < bitLength; i++) {
                bitCode = bitCode << 1;
                bitCode = bitCode | bitIn.getBit();
            }
            bitset<8> print_bitCode(bitCode);
            cerr << print_bitCode << "]";
            
            // create leaf node in Huffman Tree based on code length and pattern
            root = buildTree2(root, bitLength, bitCode, static_cast<unsigned char>(i));
        }
        cerr << endl;
        
        // create code symbol for character to add to Code Table
        CodeSymbol temp;
        temp.length = bitLength;
        temp.pattern = bitCode;
        table.add(static_cast<unsigned char>(i), temp);
        
    }
    
    // read in total count of characters from encoded file as 32-bit byte
    cerr << "\nTotal character count (from input encoded file) = ";
    for (int i = 0; i < 4; i++) {
        totalCount += bitIn.getByte() << (i * 8);
    }
    cerr << " (" << totalCount << ")" << endl;
}

HuffmanTree::~HuffmanTree() {
    clear();
}

Node<unsigned char, unsigned int>* HuffmanTree::buildTree(
                        Heap<Node<unsigned char, unsigned int>*,
                        std::vector<Node<unsigned char, unsigned int>*>,
                        Compare<unsigned char, unsigned int>> priorityQueue) {
    
    while (priorityQueue.getSize() > 1) {
        
        // combine two lowest priority and add back to priority queue as a branch
        Node<unsigned char, unsigned int>* first = priorityQueue.pop();
        Node<unsigned char, unsigned int>* second = priorityQueue.pop();
        
        unsigned int frequencySum = first->getPriority() + second->getPriority();
        Node<unsigned char, unsigned int>* combined =
        new Node<unsigned char, unsigned int>(frequencySum, first, second);
        
        priorityQueue.push(combined);
        priorityQueue.verify();
    }
    
    return priorityQueue.pop();
}

// rebuild Huffman Tree from encoded file
Node<unsigned char, unsigned int>* HuffmanTree::buildTree2(Node<unsigned char, unsigned int>* current,
                                                    int bitLength, unsigned long long bitCode,
                                                    unsigned char character) {
    if (bitLength == 0) {
        current = new Node<unsigned char, unsigned int>(character);
        return current;
    }
    if (current == nullptr) {
        current = new Node<unsigned char, unsigned int>();
    }
    
    unsigned long long bit = bitCode & (1 << (bitLength - 1));
    bit = bit >> (bitLength - 1);
    
    if (bit == 0) {
        current->getLeft() = buildTree2(current->getLeft(), bitLength - 1, bitCode, character);
    } else {
        current->getRight() = buildTree2(current->getRight(), bitLength - 1, bitCode, character);
    }
    return current;
}

void HuffmanTree::makeCode(CodeTable& table) {
    
    // first check if tree is empty
    if (!root) {
        cerr << "Huffman Tree is empty!" << endl;
        exit(EXIT_FAILURE);
    }
    makeCodeHelper(root, table, 0, 0);
}

void HuffmanTree::makeCodeHelper(Node<unsigned char, unsigned int>* current,
                                 CodeTable& table, int length, unsigned long long pattern){
    
    // at leaf node, add character's pattern and length as a code symbol in Code Table
    if (!current->getLeft() && !current->getRight()) {
        CodeSymbol result;
        result.length = length;
        result.pattern = pattern;
        table.add(current->getData(), result);
        return;
    }
    
    // add 0 to pattern if traversing left, otherwise 1
    makeCodeHelper(current->getLeft(), table, length + 1,
                   pattern << 1 | 0);
    makeCodeHelper(current->getRight(), table, length + 1,
                   pattern << 1 | 1);
}

void HuffmanTree::decode(BitInputStream& bitIn, string outfile, unsigned int totalCount) {
    
    ofstream out;
    out.open(outfile);
    
    if (!out.is_open()) {
        cerr << "Error opening output file!" << endl;
    }
    cerr << "\nDecoding input huff file..." << endl;
    
    for (int i = 0; i < totalCount; i++) {
        
        Node<unsigned char, unsigned int>* current = root;
        
        // read encoded file bit by bit and traverses down rebuilt Huffman Tree,
        // at leaf node, write character to .puff output file
        while (current->getLeft() != nullptr && current->getRight() != nullptr) {
            unsigned int bit = bitIn.getBit();
            if (bit == 0) {
                current = current->getLeft();
            } else {
                current = current->getRight();
            }
        }
        
        unsigned char character = current->getData();
        out.put(character);
    }
    out.close();
    cerr << "Decoding done..." << endl;
}

// verifies Huffman Tree is valid based on priority
void HuffmanTree::verify() {
    
    bool result = true;
    verify_helper(root, result);
    
    if (result) {
        cerr << "TREE IS VALID" << endl;
    }
}

// priority number of any subtree's parent must equal summ of
// left and right child's priority numbers
void HuffmanTree::verify_helper(Node<unsigned char, unsigned int>* current,
                                  bool& result) {
    // reached leaf node
    if (current->getRight() != nullptr && current->getLeft() != nullptr) {
        
        if (current->getPriority() != current->getLeft()->getPriority() +
            current->getRight()->getPriority()) {
            
            cerr << "Priorities do not match up!" << endl;
            cerr << "- parent: " << current->getPriority() << endl;
            cerr << "- left child + right child: " <<
            current->getLeft()->getPriority() + current->getRight()->getPriority() << endl;
            result = false;
            
        }
        verify_helper(current->getLeft(), result);
        verify_helper(current->getRight(), result);
    }
}

void HuffmanTree::verify2(const CodeTable& table) {
    
    bool result = true;
    verify2_helper(root, table, result, 0, 0);
    
    if (!result) {
        cerr << "BAD -- Tree does not match with Code Table" << endl;
    } else {
        cerr << "GOOD -- Tree matches with Code Table" << endl;
    }
}

void HuffmanTree::verify2_helper(Node<unsigned char, unsigned int>* current,
                const CodeTable& table, bool& result, unsigned long long code,
                  int length) {
    
    // if character/pattern/length do not match with Code Table, tree is invalid
    if (current != nullptr) {
        
        if (current->getLeft() == nullptr && current->getRight() == nullptr) {
            unsigned char character = current->getData();
            CodeSymbol temp = table.getCodeSymbol(character);
            
            if (code != temp.pattern && length != temp.length) {
                result = false;
            }
        }
        verify2_helper(current->getLeft(), table, result, code << 1 | 0,
                       length + 1);
        verify2_helper(current->getRight(), table, result, code << 1 | 1,
                       length + 1);
    }
}

// prints Huffman Tree 
void HuffmanTree::dump() {
    dumpHelper(root, 0);
}

void HuffmanTree::dumpHelper(Node<unsigned char, unsigned int>* node, int level) {
    if (node != nullptr) {
        
        dumpHelper(node->getRight(), level + 1);
        
        for (int i = 0; i < level; i++) {
            cerr << "\t";
        }
        cerr << "(";
        if (node->isBranch()) {
            cerr << node->getPriority();
        } else {
            char c = static_cast<char>(node->getData());
            cerr << (isprint(c) ? c : ' ') << ", " << node->getPriority();
        }
        cerr << ")" << endl;
        dumpHelper(node->getLeft(), level + 1);
    }
}

// clears the whole tree
void HuffmanTree::clear() {
    clearHelper(root);
}

void HuffmanTree::clearHelper(Node<unsigned char, unsigned int>*& current) {
    if (current == nullptr) return;
    clearHelper(current->getLeft());
    clearHelper(current->getRight());
    delete current;
    current = nullptr;
}

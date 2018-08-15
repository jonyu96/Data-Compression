//
//  HuffmanTree.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/6/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  Huffman Tree to create Huffman Coding for each relevant
//  character. 

#ifndef HuffmanTree_h
#define HuffmanTree_h

#include <vector>
#include <limits.h>
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>

#include "Node.h"
#include "Heap.h"
#include "FrequencyTable.h"
#include "CodeTable.h"
#include "BitInputStream.h"


class HuffmanTree {
public:
    
    // constructs Huffman Tree from Frequency Table
    HuffmanTree(const FrequencyTable& freqTable);
    
    // constructs Huffman Tree and Code Table from encoded file
    HuffmanTree(BitInputStream& bitIn, CodeTable& table, unsigned int& totalCount);
    ~HuffmanTree();
        
    // builds Code Table from Huffman Tree
    void makeCode(CodeTable& table);
    
    // decodes rest of encoded input file to output file with .puff extension
    void decode(BitInputStream& bitIn, std::string outfile, unsigned int totalCount);
    
    // verifies Huffman Tree based on priority
    void verify();
    
    // verifies rebuilt Huffman  Tree based on rebuilt Code Table
    void verify2(const CodeTable& table);
    
    // prints structure and content of Huffman tree
    void dump();
    
    // deletes tree
    void clear();
    
private:
    
    Node<unsigned char, unsigned int>* root;
    
    // builds initial Huffman Tree for encoding
    Node<unsigned char, unsigned int>* buildTree(
                            Heap<Node<unsigned char, unsigned int>*,
                            std::vector<Node<unsigned char, unsigned int>*>,
                            Compare<unsigned char, unsigned int>> priorityQueue);
    
    // rebuilds Huffman Tree from encoded .huff file for decoding
    Node<unsigned char, unsigned int>* buildTree2(
                            Node<unsigned char, unsigned int>* current,
                            int bitlength, unsigned long long bitcode,
                            unsigned char character);
    
    void makeCodeHelper(Node<unsigned char, unsigned int>* current,
                        CodeTable& table, int length, unsigned long long pattern);
    
    void verify_helper(Node<unsigned char, unsigned int>* current,
                                      bool& result);
    
    void verify2_helper(Node<unsigned char, unsigned int>* current,
                      const CodeTable& table, bool& result,
                      unsigned long long code, int length);
    void dumpHelper(Node<unsigned char, unsigned int>* node, int level);
    void clearHelper(Node<unsigned char, unsigned int>*& cur);
    
};

#endif

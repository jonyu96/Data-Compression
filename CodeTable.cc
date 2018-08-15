//
//  CodeTable.cpp
//  Assignment2
//
//  Created by Jonathan Yu on 5/6/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.

#include "CodeTable.h"

using namespace std;

// construct empty Code Table
CodeTable::CodeTable() {
    for (int i = 0 ; i < UCHAR_MAX + 1; i++) {
        CodeSymbol temp;
        temp.length = 0;
        temp.pattern = 0;
        table[i] = temp;
    }
}

// destructor
CodeTable::~CodeTable() {}

// write header and encode input text file to output .huff file
void CodeTable::encode(string infile, string outfile, unsigned int totalCount) {
    
    // open input file stream again
    ifstream in;
    in.open(infile);
    
    // open BitOutputStream
    BitOutputStream bitout(outfile);
    
    // write header to huff file
    writeHeader(bitout, totalCount);
    
    // encode each character read from input text file to output file
    cerr << "\nEncoding text file...\n" << endl;
    if (in.is_open()) {
        char c;
        while ((c = in.get()) != EOF) {
            
            unsigned char character = static_cast<unsigned char>(c);
            if (c == '\n') {
                character = '\n';
            }
            // get character's code symbol from Code Table
            CodeSymbol temp = table[character];
            int bitLength = temp.length;
            unsigned long long bitCode = temp.pattern;
            
            // write character's code pattern by bit to output
            for (int i = bitLength - 1; i >= 0; i--) {
                unsigned int bit = (bitCode >> i) & 1;
                bitout.putBit(bit);
            }
        }
        bitout.flush();
    }
    in.close(); // close input file stream
    cerr << "\n\nEncoding done..." << endl;
}

// write code symbols header to output file
void CodeTable::writeHeader(BitOutputStream& bitout,
                             unsigned int totalCount) {
    
    cerr << "\n\t\t   CODE TABLE HEADER FOR ENCODED FILE" << endl;
    cerr << "\t-- only code length and pattern are encoded to output file --\n\n";
    cerr << "HEX\t\tCharacter\t\tCode Length\t\tCode Pattern" << endl;
    cerr << "--------------------------------------";
    cerr << "--------------------------------------\n";
    
    for (int i = 0; i < UCHAR_MAX + 1; i++) {
        
        char c = i;
        CodeSymbol temp = table[i];
        unsigned char bitLength = static_cast<unsigned char>(temp.length);
        unsigned long long bitCode = temp.pattern;
        
        cerr << showbase << hex << static_cast<int>(i);
        cerr << "\t\t(" << (isprint(c) ? c : ' ') << ")";
        cerr << dec << "\t\t\t";
        
        // output length of each character's code (8-bit)
        bitout.putByte(bitLength);
        
        // if length > 0, output actual code of character (8-bit)
        if (temp.length > 0) {
            cerr << "\t\t[";
            
            // write character's code pattern by bit
            for (int i = temp.length - 1; i >= 0; i--) {
                unsigned int bit = (bitCode >> i) & 1;
                bitout.putBit(bit);
            }
            
            bitout.flush();
            cerr << "]";
        }
        cerr << endl;
    }
    
    // output total count of characters from input text file
    cerr << "\nTotal character count (from input text file) = ";
    
    unsigned int print_totalCount = totalCount;
    for (int i = 0; i < 4; i++) {
        unsigned char temp = static_cast<unsigned char>(totalCount);
        bitout.putByte(temp);
        totalCount = totalCount >> 8;
    }
    cerr << " (" << print_totalCount << ")" << endl;
}

// print Code Table, displaying HEX/Character/Code Pattern/Code Length
void CodeTable::dump() {
    
    cerr << "\n\t\tCode Table" << endl;
    cerr << "----------------------------------------------" << endl;
    cerr << "HEX\tCharacter\t[Code Pattern]: Length\n\n";
    
    for (int i = 0; i < UCHAR_MAX + 1; i++) {
        char c = i;
        CodeSymbol temp = table[i];
        
        if (temp.length > 0) {
            
            cerr << showbase << hex << static_cast<int>(c) << dec;
            cerr << "\t(";
            cerr << (isprint(c) ? c : ' ');
            cerr << ")" << "\t\t[";
            
            for (int i = temp.length - 1; i >= 0; i--) {
                cerr << ((temp.pattern & (1 << i)) ? "1" : "0");
            }
            
            cerr << "]: " << temp.length << endl;
        }
    }
}


//
//  CodeTable.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/6/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  Stores code pattern and length for all 0-255 ASCII characters

#ifndef CodeTable_h
#define CodeTable_h

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

#include "BitOutputStream.h"

// code length and pattern of a character is
// stored as a Code Symbol
struct CodeSymbol {
    int length;
    unsigned long long pattern;
};

class CodeTable {
public:
    
    CodeTable();
    ~CodeTable();
    
    // encodes input text file using Code Table to output .huff file
    void encode(std::string infile, std::string outfile, unsigned int totalCount);
    
    // prints Code Table
    void dump();
    
    // adds a character's Code Symbol to Code Table
    void add(unsigned char c, const CodeSymbol& temp) {
        table[c] = temp;
    }
    
    // return a character's Code Symbol
    CodeSymbol getCodeSymbol(unsigned char character) const{
        return table[character];
    }
    
private:
    
    // store Code Symbols
    CodeSymbol table[UCHAR_MAX + 1];
    
    // writes Code Table header to encoded output file
    void writeHeader(BitOutputStream& bitout, unsigned int totalCount);
};

#endif

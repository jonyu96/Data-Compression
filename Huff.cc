//
//  Huff.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/6/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  This program compresses input text file using Huffman Coding.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "HuffmanTree.h"
#include "FrequencyTable.h"
#include "CodeTable.h"
#include "BitOutputStream.h"

using namespace std;

int main(int argc, char** argv) {
    
    // display error if input file argument is not passed
    if (argc < 2) {
        cerr << "Input text file is required!" << endl;
        return EXIT_FAILURE;
    }
    
    // store name of input file
    string infile = argv[1];
    int infile_length = static_cast<int>(infile.length());
    
    // create output file name with .huff extension
    string outfile = infile.substr(0, infile_length - 4) + ".huff";
    
    ifstream in;
    in.open(infile);
    
    // check input file stream
    if (!in.good() || in.eof()) {
        
        cerr << "There was an error reading the input file!" << endl;
        return EXIT_FAILURE;
    }
    
    // create and print Frequency Table to store frequency of each character
    FrequencyTable frequency;
    frequency.buildTable(in);
    frequency.dump();
    
    in.close();
    
    // build, verify, and print Huffman Tree built from Frequency Table
    HuffmanTree tree(frequency);
    tree.dump();
    tree.verify();
    
    // create and print Code Table containing each character's code pattern and length
    CodeTable table;
    tree.makeCode(table);
    table.dump();
    
    unsigned int totalCount = frequency.getCount(); // total count of characters in input text file
    
    // encode input text file using Code Table into a .huff file 
    table.encode(infile, outfile, totalCount);
    
    exit(EXIT_SUCCESS);
    
}

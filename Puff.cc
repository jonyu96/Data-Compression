//
//  Puff.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/9/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits.h>

#include "CodeTable.h"
#include "HuffmanTree.h"
#include "BitInputStream.h"

using namespace std;

int main(int argc, char** argv) {
    
    // check if input file argument is passed in
    if (argc < 2) {
        cerr << "Encoded input file is required!" << endl;
        return EXIT_FAILURE;
    }
    
    // store encoded input file name
    string infile = argv[1];
    string extension = infile.substr(infile.length() - 5);
    
    // display error if encoded input file name does not have ".huff" extension
    if (extension != ".huff") {
        cerr << "Input file must be a .huff file!" << endl;
        return EXIT_FAILURE;
    }
    
    // create output decoded file with ".puff" extension
    string outfile = infile.substr(0, infile.length() - 5) + ".puff";
    
    // open BitInputStream to read in encoded .huff file
    BitInputStream bitIn(infile);
    
    // rebuild Code Table and Huffman Tree by reading in code table
    // from encoded input file
    CodeTable table;
    unsigned int totalCount = 0;
    HuffmanTree tree(bitIn, table, totalCount);
    
    // verify and print table and tree
    table.dump();
    cerr << endl;
    tree.dump();
    cerr << endl;
    tree.verify2(table);
    
    // decodes rest of encoded file into .puff file
    tree.decode(bitIn, outfile, totalCount);
    
        
    exit(EXIT_SUCCESS);
}

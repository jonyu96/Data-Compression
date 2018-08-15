//
//  BitStreamReader.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/2/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#include "BitInputStream.h"

using namespace std;

BitInputStream::BitInputStream(string infile) : in(), buffer(0), count(0) {
    in.open(infile);
    if (!in.is_open()) {
        cerr << "Error in opening input file!" << endl;
        exit(EXIT_FAILURE);
    }
}

BitInputStream::~BitInputStream() {
    in.close();
}

unsigned int BitInputStream::getBit() {
    if (count == 0) {
        buffer = in.get();
        count = 8;
    }
    
    unsigned int bit = buffer & (1 << (count - 1));
    bit = bit >> (count - 1);
    
    count = count - 1;
    return bit;
}

unsigned char BitInputStream::getByte() {
    buffer = in.get();
    count = 0;

    bitset<8> print_buffer(buffer);
    cerr << print_buffer;

    return buffer;

}



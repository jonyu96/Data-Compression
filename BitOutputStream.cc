//
//  BitOutputStream.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/2/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#include "BitOutputStream.h"

using namespace std;

BitOutputStream::BitOutputStream(string outfile) : output(), buffer(0), count(0) {
    
    output.open(outfile);
    if (!output.is_open()) {
        cerr << "Error in opening output file!" << endl;
    }
}

BitOutputStream::~BitOutputStream() {
    flush();
    output.close();
}

int BitOutputStream::putBit(unsigned int bit) {
    
    buffer = buffer << 1;
    buffer = buffer | bit;
    count++;
    
    if (count == 8) {
        flush();
    }
    return 0;
}

int BitOutputStream::putByte(unsigned char byte) {
    buffer = byte;
    count = 8;
    flush();
    
    return 0;
}

void BitOutputStream::flush() {
    if (count > 0) {
        buffer = buffer << (8 - count);
        
        print();
        
        output.put(buffer);
        count = 0;
        buffer = 0;
    }
}

void BitOutputStream::print() {
    std::bitset<8> buf(buffer);
    std::cerr << buf;
}

//
//  BitOutputStream.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/2/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#ifndef BitOutputStream_h
#define BitOutputStream_h

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

class BitOutputStream {
public:
    
    // construct bit output stream with output file name
    BitOutputStream(std::string outfile);
    ~BitOutputStream();
    
    // writes a bit of buffered bits to output file
    int putBit(unsigned int bit);
    
    // writes buffer as byte to output file
    int putByte(unsigned char byte);
    
    // adds any additional zero bits to fill current byte and writes to output file
    void flush();
    
private:
    
    // output file stream
    std::ofstream output;
    
    // buffer to hold bits
    unsigned char buffer;
    int count;
    
    void print();
    
};

#endif

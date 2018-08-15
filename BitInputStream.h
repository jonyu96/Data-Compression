//
//  BitInputStream.hpp
//  Assignment2
//
//  Created by Jonathan Yu on 5/2/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#ifndef BitInputStream_h
#define BitInputStream_h

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <cstdlib>

class BitInputStream {
public:
    
    // construct bit input stream with input file name
    BitInputStream(std::string infile);
    ~BitInputStream();
    
    // return bit of buffer
    unsigned int getBit();
    
    // return byte of buffer
    unsigned char getByte();
    
private:
    
    // input file stream
    std::ifstream in;
    
    // buffer of bits
    unsigned char buffer;
    int count;
    
};

#endif


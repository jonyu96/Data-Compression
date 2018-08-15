//
//  FrequencyTable.h
//  Assignment2
//
//  Created by Jonathan Yu on 5/4/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//
//  Stores the frequency of each 0 - 255 ASCII character
//  from input text file.

#ifndef FrequencyTable_h
#define FrequencyTable_h

#include <iostream>
#include <fstream>
#include <climits>

class FrequencyTable {
    
public:
    
    FrequencyTable();
    ~FrequencyTable();
    
    // build Frequency Table with input file stream passed in
    void buildTable(std::ifstream& in);
    
    // return total count of all characters read from input file
    unsigned int getCount() {return totalCount;}
    
    // print Frequency Table and relative frequency chart
    void dump();
    
    // return frequency of ASCII character
    unsigned int get(unsigned char c) const {
        return frequency[c];
    }
    
private:
    
    // store frequencies of 0 - 255 ASCII characters
    unsigned int frequency[UCHAR_MAX + 1];
    
    unsigned int totalCount;
    unsigned int maxFreq;
    
};

#endif

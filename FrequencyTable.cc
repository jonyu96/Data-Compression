//
//  FrequencyTable.cc
//  Assignment2
//
//  Created by Jonathan Yu on 5/4/18.
//  Copyright © 2018 Jonathan Yu. All rights reserved.
//

#include "FrequencyTable.h"

using namespace std;

FrequencyTable::FrequencyTable() : frequency{0}, totalCount(0), maxFreq(0) {}

FrequencyTable::~FrequencyTable() {}

void FrequencyTable::buildTable(ifstream& in) {
    
    if (!in.good() || in.eof()) {
        cerr << "Error in reading file!" << endl;
        exit(EXIT_FAILURE);
    }
    
    // read in each character until end of file
    char c;
    while ((c = in.get()) != EOF) {
        unsigned char character =
        static_cast<unsigned char>(c);
        if ('\n' == c) {
            character = '\n';
        }
        frequency[character]++;
        totalCount++;
        maxFreq = max(frequency[character], maxFreq);
    }
}

void FrequencyTable::dump() {
    
    cerr << "\t-FREQUENCY TABLE-\n\n";
    cerr << "HEX\t\tCharacter\tCount\t\tRelative Frequency" << endl;
    cerr << "---------------------------------";
    cerr << "---------------------------------" << endl;
    
    for (int i = 0; i < UCHAR_MAX + 1; i++) {
        cerr << showbase << hex << static_cast<int>(i) << dec;
        cerr << "\t\t(";
        char c = static_cast<char>(i);
        cerr << (isprint(c) ? c : ' ');
        cerr << ")" << "\t\t";
        cerr << frequency[i] << "\t\t";
        unsigned int freq = 50 * frequency[i] / maxFreq;
        for (int j = 0; j < freq; j++) {
            cerr << "-";
        }
        cerr << endl;
    }
    cerr << endl;
}

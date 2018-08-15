#!/bin/bash

# compiles and builds executable huff and puff programs 
#--------------------------------------------------



g++ -std=c++11 Huff.cc BitInputStream.cc BitOutputStream.cc CodeTable.cc FrequencyTable.cc HuffmanTree.cc -o huff

g++ -std=c++11 Puff.cc BitInputStream.cc BitOutputStream.cc CodeTable.cc HuffmanTree.cc -o puff

g++ -std=c++11 HeapSortTest.cc -o HeapSortTest

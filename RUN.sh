#!/bin/bash 

# RUN script
# Encode endersgame.txt file to endersgame.huff and verification data into EG_encode.txt
# Decode endersgame.huff file to endersgame.puff and verification data into EG_decode.txt
# Compares endersgame.txt and endersgame.puff using DIFF utility
# Run HeapSortTest

#----------------------------------------------------------------------------------------

./huff endersgame.txt 2> EG_encode.txt
./puff endersgame.huff 2> EG_decode.txt

diff -s endersgame.txt endersgame.puff 

./huff common-sense.txt 2> CS_encode.txt
./puff common-sense.huff 2> CS_decode.txt

diff -s common-sense.txt common-sense.puff

./HeapSortTest

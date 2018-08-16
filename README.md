# Data Compression

A data compression program that uses Huffman coding algorithm to compress and decompress files. There are a lot of moving parts to this program which are outlined and detailed below:

* Bitstreams- two utility programs, BitInputStream and BitOutputStream, are implemented to read and write streams of bits. When first encoding a text file, bits (generated using the Huffman tree) are buffered into bytes and output to an encoded file. When reading decoding/reading an encoded file, bytes are buffered into a 8-bit buffer.

* Frequency Table- reads a text file and produces a table of ASCII characters and the frequency of each character from the input. The table also generates a horizontal bar chart that captures the relative frequency of each character in a readable format.

* Priority Queue- implemented using Heapsort algorithm to build the Huffman tree.

* Huffman Tree- a data structure creating using a Priority Queue and Frequency Table to encode unique Huffman code for each character. A dump routine is implemented to show the structure of this tree in the test output files.

* Code Table- contains the length (number of bits) and bit pattern of each coded symbol. The length and pattern are stored in an unsigned long long. A dump routine is implemented to show the content and structure of the Code Table. This is also emitted to the compressed output file as a code header file and to be used for decoding.

* Huff- compresses a text file.

* Puff- Decompresses a compressed .huff file into a .puff file

## Compression Result

Text file used - endersgame.txt

File size BEFORE compression:
* [571 KB]

File size AFTER compression:
* [132 KB]

Total space saving (defined as reduction in size relative to the uncompressed size):
* [44%]

## Installing

Download project source code files and run [Build Script](https://github.com/jonyu96/Data-Compression/blob/master/BUILD.sh) on terminal: 

```
g++ -std=c++11 Huff.cc BitInputStream.cc BitOutputStream.cc CodeTable.cc FrequencyTable.cc HuffmanTree.cc -o huff

g++ -std=c++11 Puff.cc BitInputStream.cc BitOutputStream.cc CodeTable.cc HuffmanTree.cc -o puff

g++ -std=c++11 HeapSortTest.cc -o HeapSortTest
```

## Running the Tests 

Run the following script with a reasonably-sized text file (e.g. Ender's Game text): 

```
./huff (text file name).txt 2> (encoding validation test file name).txt
./puff (text file name).huff 2> (decoding validation test file name).txt

diff -s (text file name).txt (text file name).puff 
```
Verify that you get the expected compression and the original data back when expanded by comparing the original .txt file and the .puff file using the 'diff' utility.

Your (encoding validation test file name).txt should contain the following parts in a readable format: 
* Frequency Table
* Huffman Code generation of each character using Priority Queue 
* Huffman Tree structure
* Code Table (HEX code, ASCII character, and code pattern/length) 
* Code Table Header for encoded, compressed file
* Total character count encoded (from input text file)
* All encoded characters by their unique Huffman code 

Your (decoding validation test file name).txt should contain the following parts in a readable format: 
* Code Table Header read/decoded from encoded 
* Total character count decoded from encoded input file
* Original Code Table

## Contribution 

This is a class project from Professor Morris Bernstein's CSS 343 (Data Structures and Algorithms II) class. If you want to recreate your own Data Compression program, you can refer to the [Project Specs](http://courses.washington.edu/css343/bernstein/2018-q2/assignment-02.html). 

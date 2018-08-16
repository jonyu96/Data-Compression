# Data Compression

A data compression program that uses Huffman coding algorithm to compress and decompress files. There are a lot of moving parts to this program which are outlined and detailed below:

* Bitstreams- two utility programs, BitInputStream and BitOutputStream, are implemented to read and write streams of bits. When first encoding a text file, bits (generated using the Huffman tree) are buffered into bytes and output to an encoded file. When reading decoding/reading an encoded file, bytes are buffered into a 8-bit buffer.

* Frequency Table- reads a text file and produces a table of ASCII characters and the frequency of each character from the input. The table also generates a horizontal bar chart that captures the relative frequency of each character in a readable format.

* Priority Queue- implemented using Heapsort algorithm to build the Huffman tree.

* Huffman Tree- a data structure creating using a Priority Queue and Frequency Table to encode unique Huffman code for each character. A dump routine is implemented to show the structure of this tree in the test output files.

* Code Table- contains the length (number of bits) and bit pattern of each coded symbol. The length and pattern are stored in an unsigned long long. A dump routine is implemented to show the content and structure of the Code Table. This is also emitted to the compressed output file as a code header file and to be used for decoding.

* Huff- compresses a text file.

* Puff- Decompresses a compressed .huff file.

### Compression Result

Text file used - endersgame.txt

File size BEFORE compression:
* [571 KB]

File size AFTER compression:
* [132 KB]

Total space saving (defined as reduction in size relative to the uncompressed size):
* [44%]

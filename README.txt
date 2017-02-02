Author: Daniel Maida
Email: daniel.maida@wsu.edu

This is a C99 implementation of the Lempel-Ziv-Welch (LZW) compression/decompression algorithms.
This program was test in Unix/Linux environment.

How to run:

To compile this program use the Makefile provided using the command 'make'.
To run the program: ./lzw <option1> <option2> <option3>

Example: To compress the text file 'mobydick.txt'

./lzw -encode -input mobydick.txt -output mobyCompressed

To decompress:

./lzw -decode -input mobyCompressed -output mobyDecompressed.txt

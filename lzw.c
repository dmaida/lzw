#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 600000

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;
  Bits* inBits = newBits(input);
  Bits* outBits = newBits(output);

  unsigned int bits = 0;

  readBits(inBits, &bits,1);
  char* c =  malloc(4);
  c[0] = (char) bits;
  Sequence* W = newSequence(c);
  //free(c);
  while (readBits(inBits, &bits,1)) {
    c[0] = (char) bits;
    Sequence* X = appendSeq(W, c);
    if (search(table, X) != NULL) {
      W = copySequence(X);
      insertHash(table, W , nextCode);
    } else {
      printf("---------------------------\n");
      printf("word %s\n", W->key);
      int b = search(table, W);
      printf("code == %x\n", b);
      writeBits(outBits, b, 16);
      insertHash(table, X , nextCode);
    }
  }
  //printHashTable(table);
	destruct(table);
}

void stuff(FILE* input, FILE* output) {

}

//encode	an	input	stream,	writing	to	an	output	stream
//decode	an	input	stream,	writing	to	an	output	stream

/*
Encoding

Initialize dictionary D and insert characters 0 through 255
as single character sequences, each with their code set to
their respective character value.
integer nextCode = 256
Sequence W = read the first byte of data
  while (there is still data to be read) {
    Character C = next byte read from input
    Sequence X = W concatenated with C
    if (Sequence X is found in dictionary D) {
      Sequence W = Sequence X
    } else {
      find Sequence W in dictionary D and
      output the code assigned to Sequence W
      if more codes are permitted, then
        insert Sequence X into dictionary D,
          assigning nextCode as its code
        increment nextCode by 1
      set Sequence W to the single character C
    }
}
find Sequence W in D and output its assigned code

*/

#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 10

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  //initializeDict(table);  //Insert characters 0 through 255
  int nextCode = 256;
  Bits* b = newBits(input);


  unsigned int bits = 0;
  while (readBits(b, &bits,1)) {
    printf("%c\n",bits);
    char* c =  malloc(4);
    c[0] = (char) bits;
    Sequence* W = newSequence(c);
    insertHash(table, W , nextCode);
    free(c);
  }

  printHashTable(table);
	destruct(table);
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

#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 300

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;
  Bits* inBits = newBits(input);
  Bits* outBits = newBits(output);

  unsigned int bits = 0;

  readBits(inBits, &bits,1);
  char* c = malloc(0);
  memcpy(c, (char*)&bits, 2);
  Sequence* W = newSequence(&c[0]);
  printf("Seq->word: %s\n", W->key);
  //free(c);
  while (readBits(inBits, &bits,1)) {
    memcpy(c, (char*)&bits, 2);
    Sequence* X = appendSeq(W, &c[1]);
    printf("Seq->word: %s\n", X->key);
    if (searchForSeq(table, X) != -1) {
      W = copySequence(X);
    } else {
      int b = searchForSeq(table, W);
      writeBits(outBits, b, 16);
      insertHash(table, X , nextCode);
      nextCode++;
      W = newSequence(c);
    }
  }
  //printHashTable(table);
	destruct(table);
}

void stuff(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255
  int nextCode = 256;



  Sequence* A = newSequence("aa");
  Sequence* B = newSequence("aabasd");
  Sequence* C = newSequence("aabb");
  Sequence* D = newSequence("aab");

  Sequence* X = newSequence("aaaaaa");

  insertHash(table, A , nextCode);
  //nextCode++;
  insertHash(table, B , 22322);
  //nextCode++;
  insertHash(table, C , nextCode);
  //nextCode++;
  insertHash(table, D , nextCode);

  if (searchForSeq(table, X) == -1) {
    printf("Did not find X\n");
  }

  int searchForSeqA = searchForSeq(table, A);
  printf("searchForSeq A : %i\n", (searchForSeqA));


  int searchForSeqB = searchForSeq(table, B);
  printf("searchForSeq B : %i\n", searchForSeqB);

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

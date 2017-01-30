#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 60000

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;

  Bits* outBits = newBits(output);

  int charRead = fgetc(input);
  char* firstByte = malloc(8);
  firstByte[0] = (char) charRead;
  Sequence* W = newSequence(firstByte);
  free(firstByte);
  char* c = malloc(16);

  while((charRead = fgetc(input)) != EOF) {
    c[0] = (char) charRead;
    Sequence* X = copySequence(W);
    appendSeq(X, c);
    if (searchForSeq(table, X) != -1) {
      W = copySequence(X);
    } else {
      int b = searchForSeq(table, W);
      writeBits(outBits, b);
      insertHash(table, X , nextCode);
      nextCode++;
      W = newSequence(c);
    }
    deleteSeq(X);
  }
  int a = searchForSeq(table, W);
  writeBits(outBits, a);
  //printHashTable(table);
  deleteSeq(W);
  deleteBits(outBits);
  free(c);
	destruct(table);
}

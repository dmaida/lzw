#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 60000

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;

  Bits* outBits = newBits(output);

  int charRead = fgetc(input);
  char* firstByte = calloc(16, sizeof(char));
  firstByte[0] = (char) charRead;
  Sequence* W = newSequence(firstByte);
  free(firstByte);
  char* c = (char*) calloc(16, sizeof(char));

  while((charRead = fgetc(input)) != EOF) {
    c[0] = (char) charRead;
    Sequence* X = copySequence(W);
    appendSeq(X, c);
    if (searchForSeq(table, X) != -1) {
      deleteSeq(W);
      W = copySequence(X);
      deleteSeq(X);
    } else {
      insertHash(table, X , nextCode);
      nextCode++;
      writeBits(outBits, searchForSeq(table, W));
      deleteSeq(W);
      W = newSequence(c);
    }
  }
  writeBits(outBits, searchForSeq(table, W));
  //printHashTable(table);
  deleteSeq(W);
  deleteBits(outBits);
  free(c);
	destruct(table);
}

void decode(FILE* input, FILE* output) {











}

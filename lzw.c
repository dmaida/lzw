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

      writeBits(outBits, searchForSeq(table, W));

      if (nextCode <= 0XFFFF) {
        insertHash(table, X , nextCode);
        nextCode++;
      } else {
          deleteSeq(X);
      }
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


/*

Decode

Table T is a table of Sequences, indexed by an integer code.
The table must be large enough to hold as many codes as are
permitted by the maximum code bit width. Initialize table
T with entries 0 through 255 with each holding a single
character Sequence, one entry for each character 0 through
255, respectively.

integer previousCode gets the first code read from input
output Sequence T[previousCode]

while (there are more codes to be read) {
  integer currentCode gets the next code from input
  if currentCode is within Table T, then
    Character C = first character of T[currentCode]
  else
    Character C = first character of T[previousCode]
  if Table T is not full, then
    Sequence W gets a new sequence using
      T[previousCode] concatenated with C
    add Sequence W at the next index/code in Table T
  output Sequence T[currentCode]
  previousCode becomes the currentCode
}















*/

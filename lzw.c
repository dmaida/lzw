#include "lzw.h"

#define INITIAL_TABLE_SIZE 999983

void encode(FILE* input, FILE* output, int startBits, int maxBits) {

  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;
  Bits* outBits = newBits(output);
  char c = (char) fgetc(input);
  int charRead = 0;
  Sequence* W = newSequence(c);

  while((charRead = fgetc(input)) != EOF) {
    c = (char) charRead;
    Sequence* X = copySequence(W);
    appendSeq(X, c);
    if (searchForSeq(table, X) != -1) {
      deleteSeq(W);
      W = copySequence(X);
      deleteSeq(X);
    } else {
      putBits(outBits, startBits, searchForSeq(table, W));

      if (nextCode == (1<<startBits) && startBits < maxBits) {
        startBits++;
      }

      if (nextCode < (1<<startBits)) {
        insertHash(table, X , nextCode);
        nextCode++;
      } else {
        deleteSeq(X);
      }

      deleteSeq(W);
      W = newSequence(c);
    }
  }
  putBits(outBits, startBits, searchForSeq(table, W));
  sendRemainingBits(outBits);
  deleteSeq(W);
  deleteBits(outBits);
	destruct(table);
}

void decode(FILE* input, FILE* output, int startBits, int maxBits) {

  int tableSize = (1<<maxBits);

  Sequence** T = (Sequence**) calloc(tableSize+1, sizeof(Sequence*));

  for (unsigned int i = 0; i < 256; i++) {
    char c = (char) i;
    Sequence* seq = newSequence(c);
    T[i] = seq;
  }

  Bits* inBits = newBits(input);

  unsigned int bits = 0;
  //readBits(inBits, &bits);
  getBits(inBits, startBits, &bits);

  unsigned int count = 256;

  unsigned int previousCode = bits;

  if (previousCode > 256) {
    fprintf(stderr, "%s\n", "Corrupted file.");
    deleteBits(inBits);
    for (int i = 0; i <= tableSize; i++) {
      if (T[i] != NULL) {
        deleteSeq(T[i]);
      }
    }
    free(T);
    fclose(input);
    fclose(output);
    exit(1);
  }
  outSeq(output, T[previousCode]);

  if (count == (1<<startBits) ) {
    //printf("%s\n", "Increasing code length");
    startBits++;
  }

  while (getBits(inBits, startBits, &bits)) {
    if (count+1 == (1<<startBits) ) {
      //printf("%s\n", "Increasing code length");
      startBits++;
    }
    unsigned int currentCode = bits;
    char c;
    if (T[currentCode] != NULL) {
      c = firstChar(T[currentCode]);
    } else {
      c = firstChar(T[previousCode]);
    }
    if (count < tableSize+1) {
      Sequence* W = copySequence(T[previousCode]);
      W = appendSeq(W, c);
      T[count] = W;
      if (previousCode > count) {
      }
      //printf("count = %i\n", count);
      count++;
    }

    //printf("%s\n", "Before Outputting code");
    outSeq(output, T[currentCode]);
    //printf("%s\n", "After Outputting code");
    previousCode = currentCode;
  }
/*
  for (int i = 0; i <= tableSize; i++) {
    if (T[i] != NULL) {
      deleteSeq(T[i]);
    }
  }
  free(T);
  deleteBits(inBits);
*/
}

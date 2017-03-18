#include "lzw.h"

#define INITIAL_TABLE_SIZE 1000000

void encode(FILE* input, FILE* output) {
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
      //writeBits(outBits, searchForSeq(table, W));
      putBits(outBits, 16, searchForSeq(table, W));
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
  //writeBits(outBits, searchForSeq(table, W));
  putBits(outBits, 16, searchForSeq(table, W));
  deleteSeq(W);
  deleteBits(outBits);
	destruct(table);
}

void decode(FILE* input, FILE* output) {

  int tableSize = 0XFFFF;

  Sequence** T = (Sequence**) calloc(tableSize+1, sizeof(Sequence*));

  for (unsigned int i = 0; i < 256; i++) {
		char c = (char) i;
		Sequence* seq = newSequence(c);
    T[i] = seq;
	}

  Bits* inBits = newBits(input);

  unsigned int bits = 0;
  readBits(inBits, &bits);
  int count = 256;

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

  while (readBits(inBits, &bits)) {

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
     count++;
   }
     outSeq(output, T[currentCode]);
     previousCode = currentCode;
   }

   for (int i = 0; i <= tableSize; i++) {
     if (T[i] != NULL) {
       deleteSeq(T[i]);
     }
   }
   free(T);
   deleteBits(inBits);
}

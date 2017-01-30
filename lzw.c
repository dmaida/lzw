#include "lzw.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 300

void encode(FILE* input, FILE* output) {
  HashTable* table = createTable(INITIAL_TABLE_SIZE);  //Initialize dictionary D
  initializeDict(table);  //Insert characters 0 through 255

  int nextCode = 256;

  Bits* outBits = newBits(output);

  int charRead = fgetc(input);
  char* firstByte = malloc(8);
  firstByte[0] = (char) charRead;
  Sequence* W = newSequence(firstByte);

  char* c = malloc(16);

  while((charRead = fgetc(input)) != EOF) {
    c[0] = (char) charRead;
    Sequence* X = copySequence(W);
    appendSeq(X, c);
    if (searchForSeq(table, X) != -1) {
      printf("found '%s'\n", X->key);
      W = copySequence(X);
    } else {
      printf("searching for '%s' \n", W->key);

      printf("W '%s' \n", W->key);
      printf("X '%s' \n", X->key);

      int b = searchForSeq(table, W);
      writeBits(outBits, b);

      printf("Inserting = '%s' \n",X->key );
      insertHash(table, X , nextCode);
      nextCode++;
      W = newSequence(c);
    }
  }
  int a = searchForSeq(table, W);
  writeBits(outBits, a);
  printHashTable(table);
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

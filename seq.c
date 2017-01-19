#include "seq.h"
#define Initial_Size 8

Sequence* newSequence(char* k) {
  Sequence* newSequence = malloc(sizeof(Sequence));
  newSequence->key =  malloc(strlen(k)+Initial_Size+1);
  strcpy(newSequence->key, k);
  newSequence->size = Initial_Size+1+strlen(k);
  newSequence->count = strlen(k);
  return newSequence;
}

char firstChar(Sequence* seq) {
  char firstChar = seq->key[0];
  return firstChar;
}

Sequence* copySequence(Sequence* seq) {
  return newSequence(seq->key);
}

Sequence* appendSeq(Sequence* seq, char* c) {
  int seqCount = seq->count;
  int seqSize = seq->size;
  char* oldKey = seq->key;

  if (seqCount >= seqSize) {
    char* newKey = malloc(2*seqSize+1);
    strcpy(newKey, oldKey);
    strcat(newKey, c);
    free(oldKey);
    seq->key = newKey;
    seq->size = 2*seqSize+1;
    seq->count = strlen(newKey);
    printf("here ----\n");
  }

  strcat(oldKey, c);
  seq->count++;

  printf("size == %i\n", seq->size);
  printf("count == %i\n", seq->count);
  printf("key == %i\n", &(seq->key));

  return seq;
}

void printKey (Sequence* seq) {
  for (size_t i = 0; i < seq->count; i++) {
    printf("[%i]  %c \n", i, seq->key[i]);
  }
}

int cmpSeq(Sequence* firstSeq, Sequence* secondSeq) {
  int cmp = strcmp(firstSeq->key,secondSeq->key);
  printf("cmp = %i\n", cmp);
  return cmp;
}

unsigned hashCode(Sequence* seq, int hashTableSize) { //Bernstein's hashing algorithm
  //Bernstein's hashing algorithm
  char* key = seq->key;
  unsigned char *p = key;
	unsigned h = 0;
	int i;
	int len = strlen(key);

	for (i = 0; i < len; i++){
		h = 33 * h + p[i];
	}
	h = h % ((unsigned)hashTableSize);
	return h ;
}

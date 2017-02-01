#include "seq.h"
#define Initial_Size 8

Sequence* newSequence(char* k) {
  Sequence* newSequence = (Sequence*) malloc(sizeof(Sequence));
  newSequence->key = (char*) malloc(strlen(k)+Initial_Size+1);
  newSequence->size = Initial_Size+1+strlen(k);
  newSequence->count = strlen(k);
  strcpy(newSequence->key, k);
  return newSequence;
}

char firstChar(Sequence* seq) {
  char firstChar = seq->key[0];
  return firstChar;
}

Sequence* copySequence(Sequence* seq) {
  return newSequence(seq->key);
}

Sequence* appendSeq(Sequence* seq, char ch) {

  char* c = (char*) calloc(16, sizeof(char));
  c[0] = ch;

  int seqCount = seq->count;
  int seqSize = seq->size;
  char* oldKey = seq->key;
  if (seqCount >= seqSize) {
    char* newKey = (char*) calloc(2*seqSize+1, sizeof(char));
    strcpy(newKey, oldKey);
    strcat(newKey, c);
    free(oldKey);
    seq->key = newKey;
    seq->size = 2*seqSize+1;
    seq->count = strlen(newKey);
    free(newKey);
  }
  strcat(oldKey, c);
  seq->count++;
  free(c);
  return seq;
}

void outSeq(FILE* fd, Sequence* seq) {
  char* word = seq->key;
  for (int i = 0; i < strlen(word) ; i++) {
      fputc(word[i], fd);
  }
}

int cmpSeq(Sequence* firstSeq, Sequence* secondSeq) {
  int cmp = strcmp(firstSeq->key,secondSeq->key);
  return cmp;
}

void deleteSeq(Sequence* seq) {
  free(seq->key);
  free(seq);
}

unsigned hashCode(Sequence* seq, int hashTableSize) {
  //Bernstein's hashing algorithm
  char* key = seq->key;
  unsigned char *p = (unsigned char*)key;
	unsigned h = 0;
	int i;
	int len = strlen(key);

	for (i = 0; i < len; i++){
		h = 33 * h + p[i];
	}
	h = h % ((unsigned)hashTableSize);
	return h ;
}

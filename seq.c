#include "seq.h"
#define INIT_SIZE 16

Sequence* newSequence(char k) {
  Sequence* newSequence = (Sequence*) malloc(sizeof(Sequence));
  newSequence->key = (char*) calloc(INIT_SIZE+1, sizeof(char));
  newSequence->size = INIT_SIZE+1;
  newSequence->count = 1;
  newSequence->key[0] = k;
  return newSequence;
}

char firstChar(Sequence* seq) {
  char firstChar = seq->key[0];
  return firstChar;
}

Sequence* copySequence(Sequence* seq) {
  Sequence* dupSeq =  (Sequence*) malloc(sizeof(Sequence));
  dupSeq->size = seq->size;
  dupSeq->count = seq->count;
  char* tempKey = (char*) calloc(seq->size, sizeof(char));
  for (int i = 0; i < seq->count; i++) {
    tempKey[i] = seq->key[i];
  }
  dupSeq->key = tempKey;
  return dupSeq;
}

Sequence* appendSeq(Sequence* seq, char ch) {
  if (seq->count >= seq->size) {
    char* newKey = (char*) calloc(2*seq->size, sizeof(char));
    for (int i = 0; i < seq->count; i++) {
      newKey[i] = seq->key[i];
    }
    free(seq->key);
    seq->key = newKey;
    seq->size = 2*seq->size;
  }
  seq->key[seq->count++] = ch;
  return seq;
}

void outSeq(FILE* fd, Sequence* seq) {
  char* word = seq->key;
  for (int i = 0; i < seq->count; i++) {
      fputc(word[i], fd);
  }
}

bool cmpSeq(Sequence* firstSeq, Sequence* secondSeq) {
  if (firstSeq->count != secondSeq->count) {
    return false;
  }
  for (int i = 0; i < firstSeq->count; i++) {
    if (firstSeq->key[i] != secondSeq->key[i]) {
      return false;
    }
  }
  return true;
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
	int len = seq->count;

	for (i = 0; i < len; i++){
		h = 33 * h + p[i];
	}
	h = h % ((unsigned)hashTableSize);
	return h ;
}

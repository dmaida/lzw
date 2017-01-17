#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "seq.h"

Sequence* newSequence(char* k, int size) {
  Sequence* newSequence = malloc(sizeof(Sequence));
  newSequence->key =  malloc(sizeof(k)+1);
  strcpy(newSequence->key, k);
  newSequence->size = size;
  return newSequence;
}

char firstChar(Sequence* seq) {
  char firstChar = seq->key[0];
  return firstChar;
}

Sequence* copySequence(Sequence* seq) {
  return newSequence(seq->key, seq->size);
}

Sequence* appendSeq(Sequence* seq, char* c) {
  char* newKey = malloc(sizeof(seq->key) + sizeof(c)+1);
  char* oldKey = seq->key;
  strcat(newKey, oldKey);
  strcat(newKey, c);
  free(oldKey);
  seq->key = newKey;
  seq->size = strlen(newKey);
  return seq;
}

void printKey (Sequence* seq) {
  for (size_t i = 0; i < seq->size; i++) {
    printf("[%i]  %c \n", i, seq->key[i]);
  }
}

int cmpSeq(Sequence* firstSeq, Sequence* secondSeq) {
  int cmp = strcmp(firstSeq->key,secondSeq->key);
  printf("cmp = %i\n", cmp);
  return cmp;
}

unsigned seqHash(Sequence* seq) {

}

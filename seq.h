#ifndef SEQ_H
#define SEQ_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct _sequence{
    int size;
    int count;
    char* key;
} Sequence;

Sequence* newSequence(char* key);

char firstChar(Sequence* seq);

Sequence* copySequence(Sequence* seq);

Sequence* appendSeq(Sequence* seq, char ch);

void outSeq(FILE* fd, Sequence* seq);

int cmpSeq(Sequence* firstSeq, Sequence* secondSeq);

unsigned hashCode(Sequence* seq, int hashTableSize);

void deleteSeq(Sequence* seq);

#endif

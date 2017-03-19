#ifndef BITS_H
#define define BITS_H

#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef struct _bits {
  unsigned int extraBits; //remainding bits
  unsigned int bitCount;
  FILE* fd;
}Bits;

Bits* newBits(FILE* fd);

void deleteBits(Bits* b);

bool readBits(Bits* b, unsigned int *bits);

bool writeBits(Bits* b, unsigned int bits);

bool flushBits(Bits* b);

void putBits(Bits* b, int nBits, int code);

bool getBits(Bits* b, int nBits, unsigned int *bits);

void sendRemainingBits(Bits* b);


#endif

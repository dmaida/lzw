#ifndef BITS_H
#define define BITS_H

#include <stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _bits {
  unsigned int extraBits; //remainding bits
  unsigned int bitCount;
  FILE* fd;
}Bits;

Bits* newBits(FILE* fd);

void deleteBits(Bits* b);

bool readBits(Bits* b, unsigned int *bits, unsigned int count);

bool writeBits(Bits* b, unsigned int bits, unsigned int count);

bool flushBits(Bits* b);


#endif

#ifndef BITS_H
#define define BITS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct _bitsThing {
  unsigned int extraBits;
  unsigned int extraCount;
  FILE* fd;
}BitsThing;

BitsThing* newBitsThing(FILE* fd);

void deleteBitsThing(BitsThing* bt);

bool readBits(BitsThing* bit, unsigned int nBits, unsigned int* destination);

bool writeBits(BitsThing* bt, unsigned int nBits, unsigned int source);

bool flushBits(BitsThing* bt);


#endif

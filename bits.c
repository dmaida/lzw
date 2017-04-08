#include "bits.h"

Bits* newBits(FILE* fd) {
  Bits* result = (Bits*) malloc(sizeof(Bits));
  result->fd = fd;
  result->extraBits = 0;
  result->bitCount = 0; /* Number of bits extra bits*/
  return result;
}

void deleteBits(Bits* b) {
  free(b);
}

void writeBits(Bits* b, int nBits, int code){
  /*
  nBits is the number of bits to write.
  code is the code that is going be written.
  */
  unsigned int c = 0;
  int unsigned extraBits = b->extraBits;
  int bitCount = b->bitCount;

  bitCount += nBits;
  code &= (1 << nBits) - 1;

  extraBits = (extraBits << nBits) | code;

  while (bitCount >= CHAR_BIT) {
  	bitCount -= CHAR_BIT;
  	c = extraBits >> bitCount;
  	fputc(c, b->fd);
  	extraBits = extraBits ^ (c << bitCount); /* Bitwise xor*/
  }
}

bool readBits(Bits* b, int nBits, unsigned int *bits) {
    /*
    nBits is the number of bits to read.
    Which should be between 8 and 24 bits.
    *bits where the bits read are going to be saved.
    */
    int c = 0;
    int unsigned extraBits = b->extraBits;
    int bitCount = b->bitCount;

    while (bitCount < nBits) {
      if ((c = fgetc(b->fd)) == EOF){
        return false;
      }
      bitCount += CHAR_BIT;
      extraBits = (extraBits << CHAR_BIT) | c;
    }
    bitCount -= nBits;
    c = extraBits >> bitCount;
    extraBits = extraBits ^ (c << bitCount);
    *bits = c;
    b->extraBits = extraBits;
    b->bitCount = bitCount;
    return true;
}

void flushBits(Bits* b) {
  char c;
  int unsigned extraBits = b->extraBits;
  int bitCount = b->bitCount;
  if (bitCount != 0){
    c = extraBits << (CHAR_BIT - bitCount);
  	fputc(c, b->fd);
  }
}

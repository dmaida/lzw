#include "bits.h"

static int numOverflow = 0;
static unsigned int overflow = 0;

Bits* newBits(FILE* fd) {
  Bits* result = (Bits*) malloc(sizeof(Bits));
  result->fd = fd;
  result->extraBits = 0;
  result->bitCount = 0;
  return result;
}

void deleteBits(Bits* b) {
  free(b);
}

void writeBits(Bits* b, int nBits, int code){
  unsigned int c;

  numOverflow += nBits;
  code &= (1 << nBits) - 1;

  overflow = (overflow << nBits) | code;

  while (numOverflow >= CHAR_BIT) {
  	numOverflow -= CHAR_BIT;
  	c = overflow >> numOverflow;
  	fputc(c, b->fd);
  	overflow = overflow ^ (c << numOverflow); //bitwise xor
  }
}

bool readBits(Bits* b, int nBits, unsigned int *bits) {
    int c;
    static int numOverflow = 0;
    static int unsigned overflow = 0;

    while (numOverflow < nBits) {
      if ((c = fgetc(b->fd)) == EOF){
        return false;
      }
      numOverflow += CHAR_BIT;
      overflow = (overflow << CHAR_BIT) | c;
    }
    numOverflow -= nBits;
    c = overflow >> numOverflow;
    overflow = overflow ^ (c << numOverflow);
    *bits = c;
    return true;
}

void sendRemainingBits(Bits* b) {
  char c;
  if (numOverflow != 0){
    c = overflow << (CHAR_BIT - numOverflow);
  	fputc(c, b->fd);
  }
}

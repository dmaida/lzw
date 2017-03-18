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

bool readBits(Bits* b, unsigned int *bits) {
  unsigned int code = 0;
  int firstByte = fgetc(b->fd);
  int secondByte = fgetc(b->fd);
  code = (firstByte << 8) | secondByte;
  *bits = code;
  if (firstByte == EOF) {
    return false;
  }
  if (secondByte == EOF) {
    return false;
  }
  return true;
}
void putBits(Bits* b, int nBits, int code){
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

bool writeBits(Bits* b,  unsigned int bits) {
  unsigned int firstByte = (bits >> 8) & 0xFF;
  unsigned int secondByte = bits & 0xFF;
  fputc(firstByte, b->fd);
  fputc(secondByte, b->fd);
  return true;
}

bool flushBits(Bits* b) {
  return true;
}

#include "bits.h"

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

bool readBits(Bits* b, unsigned int *bits, unsigned int count) {
  unsigned int code = 0;
  int firstByte = fgetc(b->fd);
  int secondByte = fgetc(b->fd);
  if (firstByte == EOF) {
    return false;
  }
  code = (firstByte << 8) | secondByte;
  *bits = code;
  return true;
}

bool writeBits(Bits* b,  unsigned int bits, unsigned int count) {
  assert(count == 16);
  assert(b != NULL);
  printf("bits %x\n", bits);
  unsigned int firstByte = (bits >> 8) & 0xFF;
  unsigned int secondByte = bits & 0xFF;
  printf("firstByte = %x\n", firstByte);
  printf("secondByte = %x\n", secondByte);
  fputc(firstByte, b->fd);
  fputc(secondByte, b->fd);
  return true;
}

bool flushBits(Bits* b) {
  return true;
}

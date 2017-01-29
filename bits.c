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
  printf("Reading\n");
  unsigned int code = 0;
  printf("bits _> %x\n", (*bits));
  int firstByte = fgetc(b->fd);
  int secondByte = fgetc(b->fd);


  printf("firstByte = %x\n", firstByte);
  printf("secondByte = %x\n", secondByte);

  code = (firstByte << 8) | secondByte;
  printf("code = %x\n", code);
  *bits = code;
  if (code == EOF) {
    fputc(firstByte, b->fd);
    return false;
  }
  return true;
}

bool writeBits(Bits* b,  unsigned int bits, unsigned int count) {
  assert(count == 16);
  assert(b != NULL);
  printf("writing\n");
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

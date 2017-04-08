#include "bits.h"
static int extraBits = 0;
static unsigned int bitCount = 0;
Bits* newBits(FILE* fd) {
  Bits* result = (Bits*) malloc(sizeof(Bits));
  result->fd = fd;
  return result;
}
void deleteBits(Bits* b) {
  free(b);
}
void writeBits(Bits* b, int nBits, int code){
  unsigned int c;
  extraBits += nBits;
  code &= (1 << nBits) - 1;
  bitCount = (bitCount << nBits) | code;
  while (extraBits >= CHAR_BIT) {
  	extraBits -= CHAR_BIT;
  	c = bitCount >> extraBits;
  	fputc(c, b->fd);
  	bitCount = bitCount ^ (c << extraBits); //bitwise xor
  }
}
bool readBits(Bits* b, int nBits, unsigned int *bits) {
    int c;
    static int extraBits = 0;
    static int unsigned bitCount = 0;
    while (extraBits < nBits) {
      if ((c = fgetc(b->fd)) == EOF){
        return false;
      }
      extraBits += CHAR_BIT;
      bitCount = (bitCount << CHAR_BIT) | c;
    }
    extraBits -= nBits;
    c = bitCount >> extraBits;
    bitCount = bitCount ^ (c << extraBits);
    *bits = c;
    return true;
}
void flushBits(Bits* b) {
  char c;
  if (extraBits != 0){
    c = bitCount << (CHAR_BIT - extraBits);
  	fputc(c, b->fd);
  }
}

#include "bits.h"

Bits *newBits(FILE *fd)
{
    Bits *result = (Bits *)malloc(sizeof(Bits));
    result->fd = fd;
    result->extraBits = 0;
    result->bitCount = 0;
    return result;
}

void deleteBits(Bits *b)
{
    free(b);
}

void writeBits(Bits *b, int nBits, int code)
{
    unsigned int c = 0;
    static int numOverflow = 0;
    static int unsigned overflow = 0;

    numOverflow += nBits;
    code &= (1 << nBits) - 1;

    overflow = (overflow << nBits) | code;

    while (numOverflow >= CHAR_BIT)
    {
        numOverflow -= CHAR_BIT;
        c = overflow >> numOverflow;
        fputc(c, b->fd);
        overflow = overflow ^ (c << numOverflow);
    }
    b->extraBits = overflow;
    b->bitCount = numOverflow;
}

bool readBits(Bits *b, int nBits, unsigned int *bits)
{
    int c = 0;
    static int numOverflow = 0;
    static int unsigned overflow = 0;

    while (numOverflow < nBits)
    {
        if ((c = fgetc(b->fd)) == EOF)
        {
            return false;
        }
        numOverflow += CHAR_BIT;
        overflow = (overflow << CHAR_BIT) | c;
    }
    numOverflow -= nBits;
    c = overflow >> numOverflow;
    overflow = overflow ^ (c << numOverflow);
    *bits = c;

    b->extraBits = overflow;
    b->bitCount = numOverflow;
    return true;
}

void flushBits(Bits *b)
{
    char c = 0;
    if (b->bitCount != 0)
    {
        c = b->extraBits << (CHAR_BIT - b->bitCount);
        fputc(c, b->fd);
    }
}

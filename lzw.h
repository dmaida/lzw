#ifndef LZW_H
#define LZW_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "hash.h"
#include "seq.h"
#include "bits.h"

void encode(FILE* input, FILE* output, int startBits, int maxBits);
void decode(FILE* input, FILE* output, int startBits, int maxBits);

#endif

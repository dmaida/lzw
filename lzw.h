#ifndef LZW_H
#define LZW_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "seq.h"
#include "bits.h"

void encode(FILE* input, FILE* output);
void decode(int bits, int maxbits, FILE* input, FILE* output);

void stuff(FILE* input, FILE* output);



#endif

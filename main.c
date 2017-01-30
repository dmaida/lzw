#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lzw.h"

int main(int argc, char* argv[]){
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	encode(input, output);

	fclose(input);
	fclose(output);


	return 0;
}

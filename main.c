#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lzw.h"

int main(int argc, char* argv[]){
	printf("Main");
	for (int i = 0; i < argc; i++) {
		fprintf(stdout, "arg[%i] = \"%s\n", i, argv[i]);
	}

	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "r");
	encode(input, output);

	fclose(input);
	fclose(output);


	return 0;
}

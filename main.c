#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lzw.h"

int main(int argc, char* argv[]){

	int isEncode = false;
	int isDecode = false;

	FILE* input = NULL;
	FILE* output = NULL;

	for (int i = 1; i < argc; i++) {
       if (strcmp("-encode", argv[i]) == 0) {
    			isEncode = true;
          continue;
       }
       if (strcmp("-decode", argv[i]) == 0) {
				 	isDecode = true;
          continue;
       }
       if (strcmp("-input", argv[i]) == 0) {
          input = fopen(argv[i+1], "r");
          continue;
       }
			 if (strcmp("-output", argv[i]) == 0) {
          output = fopen(argv[i+1], "w");
          continue;
       }
   }

	 if ((input == NULL) | (output == NULL) ) {
	 		fprintf(stderr, "%s\n", "Input file does not exist. Or output name not specified");
			if (input != NULL) {
				fclose(input);
			}
			if (output != NULL) {
				fclose(output);
			}
			exit(1);
	 }
	 if (isEncode == isDecode) {
	 	fprintf(stderr, "%s\n", "Invalid Option");
		fclose(input);
		fclose(output);
		exit(1);
	 }

	 if (isEncode) {
	 	encode(input, output);
	 }
	 else {
		 decode(input, output);
	 }

	fclose(input);
	fclose(output);
	return 0;
}

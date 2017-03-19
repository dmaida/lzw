#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lzw.h"

void help() {

	fprintf(stderr, "%s\n", "Warning: nothing to do. Specify either -encode or -decode.");
	fprintf(stderr, "\n%s\n", "Usage:   ./lzw <option1> <option2>...  <optionN>");
	fprintf(stderr, "\n%s\n", "	Where <option>'s must be one or more of the following (in any order):");
	fprintf(stderr, "\n%s\n", "		-encode               compress the input data");
	fprintf(stderr, "\n%s\n", "		-decode               expand the compressed input");
	fprintf(stderr, "\n%s\n", "				      (exactly one of -encode or -decode must be present)");
	fprintf(stderr, "\n%s\n", "		-input <pathname>     read data from file specified by <pathname> (if -input is not specified, stdin is used)");

}

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
			help();
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
		help();
		fclose(input);
		fclose(output);
		exit(1);
	 }

	 if (isEncode) {
	 	encode(input, output, 16, 16);
	 }
	 else {
		 decode(input, output, 16, 16);
	 }

	fclose(input);
	fclose(output);
	return 0;
}

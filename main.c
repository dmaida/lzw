#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 100000

char* getNextWord(FILE* fd){
	char word[MAX_WORD_SIZE];
	int pos = 0;
	char ch;
	while((ch = fgetc(fd)) != EOF){
		if (isalnum(ch)) break;
	}
	if(ch == EOF) return NULL;
	word[pos++] = tolower(ch);
	while ((ch = fgetc(fd)) != EOF){
		if(isspace(ch) || pos >= MAX_WORD_SIZE-1) break;
		if(isalnum(ch)) word[pos++] = tolower(ch);
	}
	word[pos] = '\0';
	return strdup(word);
}

int main(int argc, char* argv[]){

	char** arg = &argv[1];

	int numOfLinesToPrint = -1;

	for (int i = 1; i < argc; i++) {

		if(argv[1][0] =='-'){
			i++;
			int digits = (int) strlen(argv[1]);
			char str[digits];
			int k = 0;
			for(int j=1; j<=digits; j++){
				if(isdigit(argv[1][j]) != 0){
					str[k] = argv[1][j];
					k++;
				}
			}
			str[k] = '\0';
			numOfLinesToPrint = atoi(str);
		}

		FILE* fd = fopen(argv[i], "r");
		if (fd == NULL){
			fprintf(stderr, "Error: file %s could not be opened for read. 	\n", *arg);
			arg++;
			continue;
		}

		char* word = getNextWord(fd);

		HashTable* table = createTable(INITIAL_TABLE_SIZE);

		while(word != NULL) {

			void* check = (void*) search(table, word);

			if(check){
				insertHash(table, word, (void*)1);
				free(word);
			}
			else{
				insertHash(table, word, (void*)1);
			}
			word = getNextWord(fd);
		}

		hashToArray(table, numOfLinesToPrint);
		destruct(table);

		fclose(fd);
		arg++;
	}
	return 0;
}

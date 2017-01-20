#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "seq.h"
#include "bits.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 300

int main(int argc, char* argv[]){
	HashTable* table = createTable(INITIAL_TABLE_SIZE);
	
	initializeDict(table);

	printHashTable(table);
	destruct(table);
	return 0;
}

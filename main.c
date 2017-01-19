#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "seq.h"
#include "bits.h"

#define MAX_WORD_SIZE 256
#define INITIAL_TABLE_SIZE 10

int main(int argc, char* argv[]){

	Sequence* firstSeq = newSequence("more");
	Sequence* secondSeq = newSequence("x");
	HashTable* table = createTable(INITIAL_TABLE_SIZE);

	insertHash(table, firstSeq, 33);
	insertHash(table, secondSeq, 12);

	printHashTable(table);


	destruct(table);
	return 0;
}

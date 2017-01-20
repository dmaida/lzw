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




	HashTable* table = createTable(INITIAL_TABLE_SIZE);



for (int i = 45; i < 50; i++) {
		char c = (char) i;
		char* pC = &c;
		printf("HERE123: %s\n", pC);
		Sequence* seq = newSequence(pC);
		insertHash(table, seq, 1);
}
	printHashTable(table);


	destruct(table);
	return 0;
}

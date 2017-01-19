#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "seq.h"
typedef struct _node{
	Sequence* word;
	unsigned int value;
	struct _node* next;
}Node;
typedef struct _hashTable{
	int count;
	int size;
	Node** array;
} HashTable;

typedef struct _sortArray{
	Node** array;
} SortedArray;

Node* createNode(Sequence* seq, unsigned int v);

HashTable* createTable(int size);

float loadFactor(HashTable* table);

void insertHash(HashTable* table, Sequence* seq, unsigned int v);

void* search(HashTable* table, Sequence* seq);

void destruct(HashTable* table);

HashTable* resizeAndRehash(HashTable* table);

void printHashTable(HashTable* table);

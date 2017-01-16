#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"

#define MAX_LOAD_FACTOR .75
#define MULTIPLYING_FACTOR 3

Node* createNode(char* k, void* v) {
	Node* newNode = malloc(sizeof(Node));
	newNode->value = v;
	newNode->word=k; 
	newNode->next = NULL;
	return newNode;
}

HashTable* createTable(int size) {
	HashTable* table = malloc(sizeof(HashTable));
	table->size = size;
	table->count = 0;
	table->array = (Node**) calloc(size,sizeof(Node*));
	return table;
}

unsigned hashCode(void *key, int hashTableSize) { //Bernstein's hashing algorithm
	unsigned char *p = key;
	unsigned h = 0;
	int i;
	int len = strlen(key);
	
	for (i = 0; i < len; i++){
		h = 33 * h + p[i];
	}
	h = h % ((unsigned)hashTableSize);
	return h ;
}

float loadFactor(HashTable* table) {
	float numbEntries = (float) table->count;
	float size = (float) table->size;
	float loadFactor = numbEntries/size;
	return loadFactor;
}

void insertHash(HashTable* table, char* k, void* v) {
	int hash = hashCode(k, table->size);

	if (search(table, k) != NULL) {
		int* change = (int*)search(table, k);
		(*change)++;
	}
	else {
		table->count++;
		Node* newNode = createNode(k, v);
		if (table->array[hash] == NULL) {
			table->array[hash] = newNode;
		} 
		else {
			Node* temp = table->array[hash];
			while (temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newNode;
		}

		if (loadFactor(table) >= MAX_LOAD_FACTOR) {
			resizeAndRehash(table);
		}
	}
}

void* search(HashTable* table, char* key) {
	Node* nodeEntry; 
	if (!key) return NULL;

	nodeEntry = table->array[hashCode(key,table->size)];
	while(nodeEntry) {
		if(strcmp(nodeEntry->word, key) == 0) {
			return &nodeEntry->value;
		}
		nodeEntry = nodeEntry->next;
	}
	return NULL;
}

void destruct(HashTable* table) {
	
	Node* nodeEntry = NULL;
	int j = 0;
	for (int i = 0; i < table->size; ++i) {

		while (table->array[i]) {
			j++;
			nodeEntry = table->array[i]->next;
			free(table->array[i]->word);
			free(table->array[i]);
			table->array[i] = nodeEntry;
		}
	}

	free(table->array);
	free(table);
}

HashTable* resizeAndRehash(HashTable* table){
	unsigned int newArraySize = (table->size)*(MULTIPLYING_FACTOR);
	Node** newArray = (Node**) calloc(newArraySize, sizeof(Node*));

    for (int i = 0; i < table->size; ++i){
        if(table->array[i] == NULL){
            continue;
        }
        Node* temp = table->array[i];
        Node* temp2 = NULL;
        table->array[i] = NULL;

        while(temp != NULL){
            temp2 = temp->next;
            temp->next = NULL;
            unsigned int hash = hashCode(temp->word, newArraySize);
            if(newArray[hash] == NULL){
                newArray[hash] = temp;
            }
            else{
                Node* temp3 = newArray[hash];
                while(temp3->next != NULL){
                    temp3 = temp3->next;
                }
                temp3->next = temp;
            }
            temp = temp2;
        }
    }

    free(table->array);
    table->size = newArraySize;
    table->array = newArray;

    return table;
}

void hashToArray(HashTable* table, int numOfLinesToPrint) {
	Node* nodeEntry = NULL; 
	int size = table->count;
	Node** arrayToBeSorted = (Node**)calloc(size,sizeof(Node*));

	int j = 0;
	for (int i = 0; i < table->size; ++i) {
		nodeEntry = table->array[i];

		while (nodeEntry != NULL) {
			arrayToBeSorted[j] = nodeEntry;
			j++;
			nodeEntry = nodeEntry->next;
		}
	}

	qsort(arrayToBeSorted, size, sizeof(Node*), cmpfunc);

	if(numOfLinesToPrint == -1 || numOfLinesToPrint > table->count){
		for (int i = 0; i < size; ++i) {
			printf("[%i] %15s %15i\n",i, arrayToBeSorted[i]->word, (int)arrayToBeSorted[i]->value);
		}
	}

	else{
		for (int i = 0; i < numOfLinesToPrint; ++i){
			printf("[%i] %15s %15i\n",i, arrayToBeSorted[i]->word, (int)arrayToBeSorted[i]->value);
		}
	}
	
	free(arrayToBeSorted);
}

int cmpfunc(const void * a, const void * b) {

	Node* nodeA = (*(Node**)a);
	Node* nodeB = (*(Node**)b);

	int valA = (int) nodeA->value;
	int valB = (int) nodeB->value;

	return (valB-valA);
}

void print(HashTable* table){
	int i = 0;
	HashTable* temp = table;
	while(i < (table->size)) {
		if (temp->array[i] == NULL) {
			printf("[%i]\n", i);
			i++;
			continue;}
			else{
				printf("[%i]%15s(%i), ",i, temp->array[i]->word, (int)temp->array[i]->value);
				Node* temp2 = temp->array[i];
				while(temp2->next != NULL){
					temp2 = temp2->next;
					printf("%15s(%i), ", temp2->word,(int)temp2->value);
				}
				printf("\n");
				i++;
			}
		}
		printf("Count = %i\n", table->count );
}

#include "hash.h"

#define MAX_LOAD_FACTOR .75
#define MULTIPLYING_FACTOR 3

Node* createNode(Sequence* seq, unsigned int v) {
	Node* newNode = malloc(sizeof(Node));
	newNode->value = v;
	newNode->word=seq;
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

void initializeDict(HashTable* table) {
	for (unsigned int i =0; i < 256; i++) {
		char* c =  malloc(8+1);
		c[0] = (char) i;
		Sequence* seq = newSequence(c);
		insertHash(table, seq, i);
		free(c);
	}
}

float loadFactor(HashTable* table) {
	float numbEntries = (float) table->count;
	float size = (float) table->size;
	float loadFactor = numbEntries/size;
	return loadFactor;
}

void insertHash(HashTable* table, Sequence* seq, unsigned int v) {
	int hash = hashCode(seq, table->size);

	if (search(table, seq) != NULL) {
		int* change = (int*)search(table, seq);
		(*change)++;
	}
	else {
		table->count++;
		Node* newNode = createNode(seq, v);
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
/*
		if (loadFactor(table) >= MAX_LOAD_FACTOR) {
			resizeAndRehash(table);
		}
*/
	}
}

void* search(HashTable* table, Sequence* seq) {
	Node* nodeEntry;
	if (!seq->key) return NULL;

	nodeEntry = table->array[hashCode(seq,table->size)];
	while(nodeEntry) {
		if(cmpSeq(nodeEntry->word, seq) == 0) {
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
			deleteSeq(table->array[i]->word);
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

void printHashTable(HashTable* table){
    for (int i = 0; i < table->size; ++i){
        printf("[%i] ",i);
        if (table->array[i] != NULL){
            Node* node = table->array[i];
            while(node){
                printf("%s", node->word->key);
                printf(", ");
                node = node->next;
            }
        }
        printf("\n");
    }
}

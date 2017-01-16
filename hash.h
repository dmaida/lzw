typedef struct _node{
	char* word;
	void* value;
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

char* getNextWord(FILE* fd);

void insert(char* word);

void print();

unsigned hashCode(void *key, int hashTableSize);

void insertHash(HashTable* table, char* key, void* value);

void* search(HashTable* table, char* key);

HashTable* createTable(int size);

Node* createNode(char* k, void* v);

HashTable* resizeAndRehash(HashTable* table);

void hashToArray(HashTable* table, int numOfLines);

int cmpfunc (const void * a, const void * b);

void destruct(HashTable* table);




typedef struct _sequence{
    int size;
    char* key;
} Sequence;

Sequence* newSequence(char* key, int size);

char firstChar(Sequence* seq);

Sequence* copySequence(Sequence* seq);

Sequence* appendSeq(Sequence* seq, char* c);

int cmpSeq(Sequence* firstSeq, Sequence* secondSeq);

unsigned seqHash(Sequence* seq);

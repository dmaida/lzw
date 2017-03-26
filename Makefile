
CFLAGS= -std=c99 -Wall -pedantic

lzw: hash.o seq.o bits.o lzw.o main.o
	gcc -g hash.o seq.o bits.o lzw.o main.o -o lzw -lm
	
hash.o: hash.c hash.h seq.h
	gcc -g -c $(CFLAGS) hash.c

seq.o: seq.c seq.h
	gcc -g -c $(CFLAGS) seq.c

bits.o: bits.c bits.h
	gcc -g -c $(CFLAGS) bits.c

lzw.o: lzw.c lzw.h hash.h seq.h bits.h
	gcc -g -c $(CFLAGS) lzw.c

main.o: main.c lzw.h
	gcc -g -c $(CFLAGS) main.c

clean:
	rm *.o lzw

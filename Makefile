
CFLAGS= -std=c99 -Wall -pedantic

lzw: main.o hash.o lzw.o seq.o bits.o
	gcc -g main.o lzw.o hash.o seq.o bits.o -o lzw

main.o: main.c lzw.h
	gcc -g -c $(CFLAGS) main.c

lzw.o: lzw.c lzw.h hash.h seq.h bits.h
	gcc -g -c $(CFLAGS) lzw.c

hash.o: hash.c hash.h seq.h
	gcc -g -c $(CFLAGS) hash.c

seq.o: seq.c seq.h
	gcc -g -c $(CFLAGS) seq.c

bits.o: bits.c bits.h
	gcc -g -c $(CFLAGS) bits.c

clean:
	rm *.o lzw

run:
	make && ./runMain test.txt && make clean

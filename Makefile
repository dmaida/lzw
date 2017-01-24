
CFLAGS= -std=c99 -Wall -pedantic

runMain: main.o hash.o seq.o bits.o
	gcc -g main.o hash.o seq.o bits.o -o runMain

main.o: main.c hash.h seq.h
	gcc -g -c $(CFLAGS) main.c

hash.o: hash.c hash.h
	gcc -g -c $(CFLAGS) hash.c

seq.o: seq.c seq.h
	gcc -g -c $(CFLAGS) seq.c

bits.o: bits.c bits.h
	gcc -g -c $(CFLAGS) bits.c

clean:
	rm *.o runMain

run:
	make && ./runMain test.txt && make clean

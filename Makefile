runMain: main.o hash.o seq.o
	gcc -g main.o hash.o seq.o -o runMain

main.o: main.c hash.h seq.h
	gcc -std=c99 -pedantic -Wall -g -c main.c

hash.o: hash.c hash.h
	gcc -std=c99 -pedantic -Wall -g -c hash.c

seq.o: seq.c seq.h
	gcc -std=c99 -pedantic -Wall -g -c seq.c

clean:
	rm *.o runMain

run:
	./runMain

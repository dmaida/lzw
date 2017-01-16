runMain: main.o hash.o
	gcc -g main.o hash.o -o runMain
	
main.o: main.c hash.h
	gcc -std=c99 -pedantic -Wall -g -c main.c
	
hash.o: hash.c hash.h
	gcc -std=c99 -pedantic -Wall -g -c hash.c

clean:
	rm *.o runMain
	

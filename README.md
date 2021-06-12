# lzw

This is a C99 implementation of the Lempel-Ziv-Welch (LZW) compression/decompression algorithms. This program was 
developed/tested in a nix/Linux environment.

## How to build

To compile this program use the Makefile provided.

```console
foo@bar:~$ make
gcc -g -c -std=c99 -Wall -pedantic hash.c
gcc -g -c -std=c99 -Wall -pedantic seq.c
gcc -g -c -std=c99 -Wall -pedantic bits.c
gcc -g -c -std=c99 -Wall -pedantic lzw.c
gcc -g -c -std=c99 -Wall -pedantic main.c
gcc -g hash.o seq.o bits.o lzw.o main.o -o lzw -lm
```

## Usage

To compress the text file 'warpeace.txt'

```console
foo@bar:~$ ./lzw -encode -input warpeace.txt -output warpeace.lzw
```

To decompress:

```console
foo@bar:~$ ./lzw -decode -input warpeace.lzw -output warpeace.txt
```

```text
Usage:

./lzw <option1> <option2>...  <optionN>

Where <option>'s must be one or more of the following (in any order):

	-encode               compress the input data

	-decode               expand the compressed input

	-input <pathname>     read data from file specified by <pathname>

	-output <pathname>    write output to file specified by <pathname>

	-startingBits <n>     Specifies a starting code size of <n> bit (the default starting code size is 16 bits) 

	-maximumBits <n>      Specifies a maximum code size of <n> bit (the default maximum code size is 16 bits) 

	Note: For an encoded file to be correctly decoded, the starting code
	size and maximum code size used with -decode operation must be the same
	as the values used to perform the -encode operation on the original file.

```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lzw.h"

void help()
{
    fprintf(stderr, "%s\n", "Warning: nothing to do. Specify either -encode or -decode.");
    fprintf(stderr, "\n%s\n", "Usage:");
    fprintf(stderr, "\n%s\n", "./lzw <option1> <option2>...  <optionN>");
    fprintf(stderr, "\n%s\n", "Where <option>'s must be one or more of the following (in any order):");
    fprintf(stderr, "\n\t%s\n", "-encode               compress the input data");
    fprintf(stderr, "\n\t%s\n", "-decode               expand the compressed input");
    fprintf(stderr, "\n\t%s\n", "-input <pathname>     read data from file specified by <pathname>");
    fprintf(stderr, "\n\t%s\n", "-output <pathname>    write output to file specified by <pathname>");
    fprintf(stderr, "\n\t%s\n", "-startingBits <n>     Specifies a starting code size of <n> bit (the default starting code size is 16 bits) ");
    fprintf(stderr, "\n\t%s\n", "-maximumBits <n>      Specifies a maximum code size of <n> bit (the default maximum code size is 16 bits) ");
    fprintf(stderr, "\n\tNote: For an encoded file to be correctly decoded, the starting code");
    fprintf(stderr, "\n\tsize and maximum code size used with -decode operation must be the same");
    fprintf(stderr, "\n\tas the values used to perform the -encode operation on the original file.\n\n");
}

int main(int argc, char *argv[])
{

    int isEncode = false;
    int isDecode = false;

    int startingBits = 16;
    int maximumBits = 16;

    FILE *input = NULL;
    FILE *output = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-encode", argv[i]) == 0)
        {
            isEncode = true;
            continue;
        }
        if (strcmp("-decode", argv[i]) == 0)
        {
            isDecode = true;
            continue;
        }
        if (strcmp("-input", argv[i]) == 0)
        {
            input = fopen(argv[i + 1], "r");
            continue;
        }
        if (strcmp("-output", argv[i]) == 0)
        {
            output = fopen(argv[i + 1], "w");
            continue;
        }
        if (strcmp("-startingBits", argv[i]) == 0)
        {
            if (argv[i + 1] != NULL)
            {
                startingBits = atoi(argv[i + 1]);
                if (startingBits == 0)
                { //invalid integer given
                    fprintf(stderr, "Unable to interpret '%s' as an integer.\n", argv[i + 1]);
                    if (input != NULL)
                    {
                        fclose(input);
                    }
                    if (output != NULL)
                    {
                        fclose(output);
                    }
                    exit(1);
                }
            }
            continue;
        }
        if (strcmp("-maximumBits", argv[i]) == 0)
        {
            if (argv[i + 1] != NULL)
            {
                maximumBits = atoi(argv[i + 1]);
                if (maximumBits == 0)
                { // invalid integer given
                    fprintf(stderr, " Error : Unable to interpret '%s' as an integer.\n", argv[i + 1]);
                    if (input != NULL)
                    {
                        fclose(input);
                    }
                    if (output != NULL)
                    {
                        fclose(output);
                    }
                    exit(1);
                }
            }
            continue;
        }
    }

    if ((input == NULL) | (output == NULL))
    {
        fprintf(stderr, "%s\n", "Error : Input file does not exist. Or output name not specified");
        help();
        if (input != NULL)
        {
            fclose(input);
        }
        if (output != NULL)
        {
            fclose(output);
        }
        exit(1);
    }
    if (isEncode == isDecode)
    {
        fprintf(stderr, "%s\n", "Error : Invalid Option");
        help();
        fclose(input);
        fclose(output);
        exit(1);
    }
    if (startingBits > maximumBits)
    {
        fprintf(stderr, "%s\n", "Error : startingBits must be less than or equal to maximumBits");
        fprintf(stderr, "%s\n", "Error : Default value for startingBits and maximumBits is 16");
        fclose(input);
        fclose(output);
        exit(1);
    }
    if (startingBits < 8 || maximumBits > 24)
    {
        fprintf(stderr, "%s\n", "Error : startingBits must be greater than or equal to 8");
        fprintf(stderr, "%s\n", "Error : maximumBits must be less than or equal to 24");
        fclose(input);
        fclose(output);
        exit(1);
    }

    if (isEncode)
    {
        encode(input, output, startingBits, maximumBits);
    }
    else
    {
        decode(input, output, startingBits, maximumBits);
    }

    fclose(input);
    fclose(output);
    return 0;
}

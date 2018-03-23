//Recovers jpegs from memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 512

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: file");
        return 1;
    }

    //open infile for reading
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "%s cannot be open.", argv[1]);
        return 2;
    }

    unsigned char *buffer = malloc(BLOCK);
    char filename[8];
    int counter = 0;
    FILE *outfile = NULL;

    //while reach EOF
    while (fread(buffer, 1, BLOCK, infile) == BLOCK)
    {
        //check if we are at the beginning of jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //generate next filename
            sprintf(filename, "%03i.jpg", counter);
            counter ++;

            //if another file exists, close it
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            //open outfile
            outfile = fopen(filename, "w");
            if (outfile == NULL)
            {
                fprintf(stderr, "Outfile cannot be open.");
                return 3;
            }
            fwrite(buffer, 1, BLOCK, outfile);
        }
        else
        {
            //fwrite in current file
            if (outfile != NULL)
            {
                fwrite(buffer, 1, BLOCK, outfile);
            }
        }
    }
    free(buffer);
    fclose(infile);
}
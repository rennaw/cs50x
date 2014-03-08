/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512
#define TOTAL_JPGS 50

// prototypes
FILE* newJPG(int num, FILE* ptr); // closes old file if there is one

int main(int argc, char* argv[])
{
    // VALIDATION

    if (argc != 1)
    {
        printf("Usage: recover does not take any arguments\n");
        printf("File card.raw must be in this directory.");
        return 1;
    }
    // INITIALIZING

    // buffer is char because that will look at hexidecimal pairs
    char* buffer = malloc(BLOCK);
    
    // file pointers
    FILE* raw = fopen("card.raw", "r");
    FILE* jpg = NULL;

    // keeping track of recovered files for naming purposes
    int numJPGs = 0;

    // JPEG signatures of two varieties
    int signature1[4] = {0xff, 0xd8, 0xff, 0xe0};
    int signature2[4] = {0xff, 0xd8, 0xff, 0xe1};

    // keeping bool flag for EOF
    bool eof = false;

    // PROCESSING
    do
    {
        // read the raw file
        if ( fread(&buffer, BLOCK, 1, raw) == 1)
        {

            // check first four bytes for JPEG signature
            bool match = false;
            for (int i = 0; i < 4; i++)
            {
                if (buffer[i] == signature1[i])
                {
                    match = true;
                }
                else if (buffer[i] == signature2[i])
                {
                    match = true;
                }
                else
                {
                    match = false;
                }
            }
            
            // if JPG signatures are in the block
            if (match)
            {
                numJPGs++;
                newJPG(numJPGs, jpg);
                fwrite(&buffer, BLOCK, 1, jpg);
            }

            // if a file has been opened for jpg
            else if (jpg != NULL)
            {
                fwrite(&buffer, BLOCK, 1, jpg);
            }

            // skip the empty block
            else {fseek(raw, BLOCK, SEEK_CUR);}
        }
        // if fread was not able to return 1, we are at eof
        else {eof = true;}

    } while (!eof && numJPGs < TOTAL_JPGS);

    // finishing
    free(buffer);
    fclose(raw);
    fclose(jpg);
    return 0;
}

FILE* newJPG(int num, FILE* ptr)
{
    // if there was a file open already
    if (ptr != NULL) {fclose(ptr);}
    
    // create file with sprintf
    char title[7];
    sprintf(title, "%3d.jpg", num);
    ptr = fopen(title, "a");
    return ptr;
}

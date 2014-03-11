/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512
#define TOTAL_JPGS 50

int main(int argc, char* argv[])
{
    // VALIDATION

    if (argc != 1)
    {
        printf("Usage: recover does not take any arguments\n");
        printf("File card.raw must be in this directory.\n");
        return 1;
    }
    // INITIALIZING

    // buffer stores the copy of block on the heap
    unsigned int* buffer = malloc(BLOCK);
    
    // file pointers
    FILE* raw = fopen("card.raw", "r");
    FILE* jpg = NULL;

    if (raw == NULL)
    {
        printf("Could not open card.raw\n");
        return 2;
    }

    // keeping track of recovered files for naming purposes
    int numJPGs = 0;

    // keeping bool flag for EOF
    bool eof = false;

    // PROCESSING
    do
    {
        // read the raw file
            if (fread(buffer, BLOCK, 1, raw) == 1)
            {

                // if JPG signatures are in the block
                if (*buffer == 0xffd8ffe0 || *buffer == 0xffd8ffe1)
                {
                    numJPGs++;
		    
		            // if there is a file already
		            if (jpg != NULL)
		            {
			            fclose(jpg);
		            }

		            // create new file with numeric name		
    		        char* title = malloc(sizeof(char) * 7);
	    	        sprintf(title, "%3d.jpg", numJPGs);
	    	        jpg = fopen(title, "a");
	    	        free(title);

	    	        // write the block to the new file
                    fwrite(buffer, BLOCK, 1, jpg);
                }

                // if a file has been opened for jpg
                else if (jpg != NULL)
                {
                    fwrite(&buffer, BLOCK, 1, jpg);
                }

                // skip empty blocks
                else 
                {
                    fseek(raw, BLOCK, SEEK_CUR);
                }
            
        }
        // if fread was not able to return 1, we are at eof
        else 
        {
            eof = true;
        }

    } while (!eof && numJPGs < TOTAL_JPGS);

    // finishing
    free(buffer);
    fclose(raw);
    fclose(jpg);
    return 0;
}


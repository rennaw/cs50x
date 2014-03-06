/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a BMP by a factor of n
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and resize factor
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save the infile's information so that we can refer to it later
    BITMAPFILEHEADER infileBF = bf;
    BITMAPINFOHEADER infileBI = bi;
    
    // edit the bfSize variable for the new file
    // bfOffBits corresponds to the size of the headers
    // which do not need to change with factor
    bf.bfSize = (bf.bfSize - bf.bfOffBits) * factor;
    bf.bfSize += bf.bfOffBits;

    // edit the size,in bytes, of new bitmap
    bi.biSizeImage = bi.biSizeImage * factor;

    // edit the dimentions of the bitmap
    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int outfilePadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int infilePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    long infileLineLength = infileBI.biWidth + infilePadding;
    long scanlineStart, scanlineFinish;

    // iterate over infile's scanlines, rescanning from 0 to factor
    for (int line = 0, biHeight = abs(infileBI.biHeight); line < biHeight; line++)
    {
        scanlineStart = ftell(inptr);
        for (int rescan = 0; rescan < factor; rescan++)
        {
            // iterate over pixels in scanline
            for (int pixel = 0; pixel < infileBI.biWidth; pixel++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
               
                 // write the pixel to file from 1 to factor
                for (int repeat = 0; repeat < factor; repeat++)
                {
                     // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // skip over padding in infile
            fseek(inptr, infilePadding, SEEK_CUR);
            
            // record the finish of the scanline
            scanlineFinish = ftell(inptr);

            // add padding for outfile
            for (int numPadChars = 0; numPadChars < outfilePadding; numPadChars++)
            {
                fputc(0x00, outptr);
            }

            // seek to the start of the line
            fseek(inptr, scanlineStart, SEEK_SET);
        }

        // seek to the end of the scanline
        fseek(inptr, scanlineFinish, SEEK_SET);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

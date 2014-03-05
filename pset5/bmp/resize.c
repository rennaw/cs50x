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

    // edit the bfSize variable for the new file
    bf.bfSize = (bf.bfSize - 54) * factor;
    bf.bfSize += 54;
    // edit the size of new bitmap
    bi.biSizeImage = bi.biSizeImage * factor;

    // edit the size of the bitmap. Using int primatives to 
    // avoid problems with multiplying LONG datatype 
    int bitmapWidth = bi.biWidth;
    int bitmapHeight = bi.biHeight;
    bi.biWidth = bitmapWidth * factor;
    bi.biHeight = bitmapHeight * factor;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines, rescanning from 0 to factor
    for (int inpt_line = 0, biHeight = abs(bi.biHeight), rescan = 0;
             inpt_line < biHeight; rescan++)
    {
        // iterate over pixels in scanline
        for (int inpt_pixel = 0; inpt_pixel < bi.biWidth; inpt_pixel++)
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

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        // if we need to rescan, move inptr back to start of line   
        if (rescan < factor) 
        {
            fseek(inptr, -bi.biWidth, SEEK_CUR);
        }
        // otherwise, increment inpt_line and continue into infile
        else 
        {
            inpt_line++;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

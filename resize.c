// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize_factor infile outfile\n");
        return 1;
    }
    //TO DO- ensure first argument is an integer

    // remember factor & filenames
    int factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (factor <= 0 || factor > 100)
    {
        fprintf(stderr, "Resize factor should be a positive integer less than or equal to 100\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }


    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER obf;
    fread(&obf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER obi;
    fread(&obi, sizeof(BITMAPINFOHEADER), 1, inptr);

    fseek(inptr, 0, SEEK_SET);

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

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    //printf("BEFORE: \nbiWIdhh: %i\nBiHeight: %i\n", bi.biWidth, bi.biHeight);

    //modify bitmapinfoheader biWidth and biHeight multiply by factor
    bi.biWidth *= factor;
    bi.biHeight *= factor;

    fseek(outptr, sizeof(BITMAPFILEHEADER) + sizeof(bi.biSize), SEEK_SET);
    fwrite(&bi.biWidth, sizeof(bi.biWidth), 1, outptr);
    fwrite(&bi.biHeight, sizeof(bi.biHeight), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine new biSizeImage and write it
    if (factor != 1)
    {
        bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
        fseek(outptr, sizeof(BITMAPFILEHEADER) + sizeof(bi.biSize) + sizeof(bi.biWidth) + sizeof(bi.biHeight) + sizeof(bi.biPlanes)
              + sizeof(bi.biBitCount) + sizeof(bi.biCompression), SEEK_SET);
        fwrite(&bi.biSizeImage, sizeof(bi.biSizeImage), 1, outptr);

        //determine new bfSize and write it
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        fseek(outptr, sizeof(bf.bfType), SEEK_SET);
        fwrite(&bf.bfSize, sizeof(bf.bfSize), 1, outptr);
    }

    //set file  to scanline
    fseek(outptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);

    // determine padding for scanlines
    int opadding = (4 - (obi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //printf("Opadding: %i\n", opadding);


    // iterate over infile's scanlines
    for (int i = 0, obiHeight = abs(obi.biHeight); i < obiHeight; i++)
    {
        // iterate over pixels in scanline
        for (int l = 0; l < factor; l++)
        {
            for (int j = 0; j < obi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile as many times as factor
                for (int k = 0; k < factor; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            if (l < factor - 1)
            {
                fseek(inptr, -(3 * obi.biWidth), SEEK_CUR);
                //printf("Step back: %i\n",-(3 * obi.biWidth));
            }

            for (int m = 0; m < padding; m++)
            {
                fputc(0x00, outptr);
                //printf("padding!");
            }
        }
        // skip over padding, if any
        fseek(inptr, opadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

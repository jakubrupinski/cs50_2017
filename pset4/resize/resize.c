/**
 * Resizes a BMP image by n-factor
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // check if n value in range
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "n value out of range! [0-100]\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        return 5;
    }

    // determine padding for scanlines of infile
    int og_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // keep infile's width and heigth
    LONG og_biWidth = bi.biWidth,
        og_biHeight = bi.biHeight;

    // calculate outfile's header parameters
    bi.biWidth *= n;
    bi.biHeight *= n;

    // determine padding for scanlines of outfile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate rest of outfile's header parameters
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(og_biHeight); i < biHeight; i++)
    {
        // write horizontal scanlines n-times (vertical resize)
        for (int v_row = 0; v_row < n; v_row++)
        {
            printf("Current position in inptr: %lu\n", ftell(inptr));
            // iterate over pixels in scanline
            for (int j = 0; j < og_biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                printf("inptr after reading: %lu\n", ftell(inptr));

                // write horizontal scanline n-times (resize)
                for (int h_row = 0; h_row < n; h_row++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // test
            printf("inptr after scanline (before padding): %lu\n", ftell(inptr));

            // skip over og_padding, if any
            fseek(inptr, og_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }

            // test
            printf("inptr after padding: %lu\n", ftell(inptr));

            if (v_row < n - 1)
            {
              // go back with seeker for vertical resizing of scanlines
              fseek(inptr, -(og_biWidth * (int)sizeof(RGBTRIPLE) + og_padding), SEEK_CUR);
            }
            printf("inptr after checking v_row: %lu\n", ftell(inptr));
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

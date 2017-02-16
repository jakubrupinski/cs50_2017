/**
 * Resizes BMP images n times (basically enlarges images)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>

#include "bmp.h"

int copy(char *infile, char *outfile);

int main (int argc, char *argv[])
{
  // check if correct number of arguments used
  if (argc != 4)
  {
    fprintf(stderr, "Usage: ./resize value infile outfile\n");
    return 1;
  }

  // keep track of argument inputs
  double value = atof(argv[1]);
  char *infile = argv[2];
  char *outfile = argv[3];

  // check if provided value is in range
  if (value > 100.0 || value < 0.0)
  {
    fprintf(stderr, "Value out of range. \n");
    return 2;
  }

  // open file input
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open the file %s. \n", infile);
    return 3;
  }

  // open output file
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fprintf(stderr, "Can not create file %s. \n", outfile);
    return 4;
  }

  // if rounded resize value is 1 - just copy the image
  if (ceil(value) == 1)
  {
    return (copy(infile, outfile));
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

  // determine original's padding for scanlines
  int og_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // resize bitmap by given value
  bi.biWidth *= value;
  bi.biHeight *= value;

  // determine resized padding
  int resized_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

  // update the rest of parameters
  bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + resized_padding) * abs(bi.biHeight);
  bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  // write BITMAPFILEHEADER to output file
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // write BITMAPINFOHEADER to output file
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
  {
      // iterate over pixels in scanline
      for (int j = 0; j < bi.biWidth; j++)
      {
          // temporary storage
          RGBTRIPLE triple;



          // read RGB triple from infile
          fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

          // write RGB triple to outfile
          fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
      }

      // skip over padding, if any
      fseek(inptr, og_padding, SEEK_CUR);

      // then add it back (to demonstrate how)
      for (int k = 0; k < resized_padding; k++)
      {
          fputc(0x00, outptr);
      }
  }

  // close infile
  fclose(inptr);

  // close outfile
  fclose(outptr);

  // success
  return 0;
}

/**
* Runs external copy program to copy the image
**/
int copy(char *infile, char *outfile)
{
  // calculate length of the command, including \0 terminator
  int command_length = strlen("./copy ") + strlen(infile) + 1 + strlen(outfile) + 1;
  char command[command_length];

  // assign whole command to variable
  snprintf(command, sizeof(command), "./copy %s %s", infile, outfile);
  // launch command in terminal, WEXITSTATUS returns exit code from child comm.

  int status = WEXITSTATUS(system(command));
  // return status from the copy program
  return status;
}

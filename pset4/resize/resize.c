/**
 * Resizes BMP images n times (basically enlarges images)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

  // read infile BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

  // read infile BITMAPINFOHEADER
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

  // if rounded resize value is 1 - just copy the image
  if (ceil(value) == 1)
  {
    copy(infile, outfile);
  }

  // resize bitmap by given value
  bi.biWidth *= round(value);
  bi.biHeight *= round(value);



  return 0;
}

int copy(char *infile, char *outfile)
{
  int command_length = strlen("./copy ") + strlen(infile) + 1 + strlen(outfile) + 1;
  char command[command_length];
  // assign whole command to command
  snprintf(command, sizeof(command), "./copy %s %s", infile, outfile);
  // launch command in terminal
  int status = system(command);
  return status;
}

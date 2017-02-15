#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main (int argc, char *argv[])
{
  // check if correct number of arguments used
  if (argc != 4)
  {
    fprintf(stderr, "Usage: ./resize float_value infile outfile\n");
    return 1;
  }

  // keep track of argument inputs
  float value = atof(argv[1]);
  char *infile = argv[2];
  char *outfile = argv[3];

  // check if provided value is in range
  if (value > 100.0 || value < 0.0)
  {
    fprintf(stderr, "Value out of range!. \n");
    return 1;
  }

  // open file input
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open the file %s. \n", infile);
    return 2;
  }

  // open output file
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fprintf(stderr, "Can not create file %s. \n", outfile);
  }





  return 0;
}

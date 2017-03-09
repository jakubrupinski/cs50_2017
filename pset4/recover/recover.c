#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int header_is_jpeg(BYTE *block_array);
void create_new_outfile(char **outfile, FILE **outptr, int *filename_counter);
void skip_nonjpeg_blocks(BYTE *byte_array, FILE *inptr);


int main(int argc, char *argv[])
{
    // check proper usage
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover filename\n");
        return 1;
    }

    // keep filenames
    int     filename_counter = 0;
    char    *infile = argv[1], *outfile = NULL;
    FILE    *inptr = fopen(infile, "r"), *outptr = NULL;
    BYTE    *byte_array = malloc(512 * sizeof(BYTE));

    // check if input file opens properly
    if (inptr == NULL)
    {
        free(byte_array);
        free(outfile);
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    // skip blocks without JPEGs
    skip_nonjpeg_blocks(byte_array, inptr);

    // keep reading memory blocks while they're 512 bytes each
    while (fread(byte_array, 1, 512, inptr) == 512)
    {
        // if next block has a new JPEG - create new file
        if (header_is_jpeg(byte_array))
        {
            create_new_outfile(&outfile, &outptr, &filename_counter);
        }

        // if not possible to write outfile - exit
        if (outptr == NULL)
        {
            free(byte_array);
            free(outfile);
            fprintf(stderr, "Could not write in %s file\n", outfile);
            return 3;
        }

        // read and write 512 bytes
        fwrite(byte_array, 1, 512, outptr);

    }

    // close files
    free(byte_array);
    free(outfile);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

int header_is_jpeg(BYTE *block_array)
{
    // check if header is the same as JPEG header, return true if it is
    if (block_array[0] == 0xff && block_array[1] == 0xd8 &&
        block_array[2] == 0xff && (block_array[3] & 0xf0) == 0xe0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void create_new_outfile(char **outfile, FILE **outptr, int *filename_counter)
{
    // if a file is open - close the old one before creating new one
    if (*outptr != NULL)
    {
        fclose(*outptr);
        free(*outfile);
    }

    // create new output file using syntax "000.jpg"
    *outfile = malloc(7 * sizeof(char) + 1);
    sprintf(*outfile, "%03i.jpg", *filename_counter);
    *outptr = fopen(*outfile, "w");
    (*filename_counter)++;
}

void skip_nonjpeg_blocks(BYTE *byte_array, FILE *inptr)
{
    fread(byte_array, 1, 512, inptr);
    while (!header_is_jpeg(byte_array))
        fread(byte_array, 1, 512, inptr);

    // seek back to first JPEG header
    fseek(inptr, -512, SEEK_CUR);
}

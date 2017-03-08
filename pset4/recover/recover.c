#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int header_is_jpeg(FILE *memcard);
void create_new_outfile(char **outfile, FILE **outptr, int *filename_counter);

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

    // skip memory blocks until a block with a JPEG is found
    while (!header_is_jpeg(inptr))
    {
        fseek(inptr, 512, SEEK_CUR);
    }

    // keep reading memory blocks while they're 512 bytes each
    while (fread(byte_array, 1, 512, inptr) == 512)
    {
        // rewind seek
        fseek(inptr, -512, SEEK_CUR);

        // if next block has a new JPEG - create new file
        if (header_is_jpeg(inptr))
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

        // read and write 512 bytes, 1 byte at a time
        for(int i = 0, arr_size = sizeof(byte_array); i < arr_size; i++)
        {
            fread(&byte_array[i], 1, 1, inptr);
            fwrite(&byte_array[i], 1, 1, outptr);
        }

    }

    // close files
    free(byte_array);
    free(outfile);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

int header_is_jpeg(FILE *memcard)
{
    BYTE *BLOCKHEADER = malloc(4 * sizeof(BYTE));
    // read first 4 bytes of current memory block
    for (int i = 0; i < 4; i++)
    {
        fread(&BLOCKHEADER[i], 1, 1, memcard);
    }

    // rewind seek back to beginning of block
    fseek(memcard, -4, SEEK_CUR);

    // check if header is the same as JPEG header, return true if it is
    if (BLOCKHEADER[0] == 0xff && BLOCKHEADER[1] == 0xd8 &&
        BLOCKHEADER[2] == 0xff && (BLOCKHEADER[3] & 0xf0) == 0xe0)
    {
        free(BLOCKHEADER);
        return 1;
    }
    else
    {
        free(BLOCKHEADER);
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

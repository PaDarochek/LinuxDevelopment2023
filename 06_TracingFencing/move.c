#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    errno = 0;
    if (argc != 3)
    {
        printf("Set exactly 2 arguments: ./move <infile> <outfile>\n");
        return -1;
    }

    FILE *infile = fopen(argv[1], "rb");
    int err_num = errno;
    if (!infile)
    {
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error opening %s: %s\n", argv[1], err_str);
        return 1;
    }

    FILE *outfile = fopen(argv[2], "wb");
    err_num = errno;
    if (!outfile)
    {
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error opening %s: %s\n", argv[2], err_str);
        fclose(infile);
        return 2;
    }

    uint8_t *buf = malloc(BUF_SIZE * sizeof(uint8_t));
    err_num = errno;
    if (!buf)
    {
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error allocating %lu bytes: %s\n", BUF_SIZE * sizeof(uint8_t), err_str);
        fclose(infile);
        fclose(outfile);
        remove(argv[2]);
        return 3;
    }

    while (!feof(infile))
    {
        int num_read = fread(buf, sizeof(uint8_t), BUF_SIZE, infile);
        if (ferror(infile))
        {
            fprintf(stderr, "Error reading %s\n", argv[1]);
            fclose(infile);
            fclose(outfile);
            remove(argv[2]);
            free(buf);
            return 4;
        }

        fwrite(buf, sizeof(uint8_t), num_read, outfile);
        if (ferror(outfile))
        {
            fprintf(stderr, "Error writing to %s\n", argv[2]);
            fclose(infile);
            fclose(outfile);
            remove(argv[2]);
            free(buf);
            return 5;
        }
    }

    free(buf);
    if (fclose(infile) == EOF)
    {
        err_num = errno;
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error closing %s: %s\n", argv[1], err_str);
        fclose(outfile);
        remove(argv[2]);
        return 6;
    }

    if (fclose(outfile) == EOF)
    {
        err_num = errno;
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error closing %s: %s\n", argv[2], err_str);
        remove(argv[2]);
        return 7;
    }

    if (remove(argv[1]))
    {
        err_num = errno;
        char * err_str = strerror(err_num);
        fprintf(stderr, "Error removing %s: %s\n", argv[1], err_str);
        remove(argv[2]);
        return 8;
    }

    return 0;
}
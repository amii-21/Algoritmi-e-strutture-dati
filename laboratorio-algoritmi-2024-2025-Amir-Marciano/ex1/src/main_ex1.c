#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/sorting/sorting.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <field> <algo>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    size_t field = atoi(argv[3]);
    size_t algo = atoi(argv[4]);

    FILE *infile = fopen(input_file, "r");
    if(!infile)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *outfile = fopen(output_file, "w");
    if(!outfile)
    {
        perror("Error opening output file");
        fclose(infile);
        return 1;
    }

    clock_t start = clock();
    sort_records(infile, outfile, field, algo);
    clock_t end = clock();

    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sorting completed in %.2f seconds\n", elapsed_time);

    fclose(infile);
    fclose(outfile);
    return 0;
}
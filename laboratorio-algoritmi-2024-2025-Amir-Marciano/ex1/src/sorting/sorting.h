#ifndef SORTING_H
#define SORTING_H
#include <stdio.h>

#include <stddef.h>

typedef struct {
    int id;         // identificatore univoco
    char *field1; // primo campo (stringa)
    int field2;     // secondo campo (intero)
    float field3;   // terzo campo (float)
} Record;

void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

int compare_field1(const void *a, const void *b);
int compare_field2(const void *a, const void *b);
int compare_field3(const void *a, const void *b);



#endif // SORTING_H
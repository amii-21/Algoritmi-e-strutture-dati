#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>

static void merge(void *base, size_t left, size_t mid, size_t right, size_t size, int (*compar)(const void*, const void*))
{
    
    size_t i, j, k;
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    void *leftArr = malloc(n1 * size);
    void *rightArr = malloc(n2 * size);

    memcpy(leftArr, (char*)base + left * size, n1 * size);
    memcpy(rightArr, (char*)base + (mid + 1) * size, n2 * size);

    i = 0; j = 0; k = left;
    while(i < n1 && j < n2)
    {
        if (compar((char*)leftArr + i * size, (char*)rightArr + j * size) <= 0)
        {
            memcpy((char*)base + k * size, (char*)leftArr + i * size, size);
            i++;
        }
        else
        {
            memcpy((char*)base + k *size, (char*)rightArr + j *size, size);
            j++;
        }
        k++;
    }
   
    while (i < n1)
    {
        memcpy((char*)base + k * size, (char*)leftArr + i * size, size);
        i++;
        k++;
    }

    while (j < n2)
    {
        memcpy((char*)base + k * size, (char*)rightArr + j * size, size);
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
    return;
}

static void merge_sort_helper(void *base, size_t left, size_t right, size_t size, int (*compar)(const void*, const void*))
{
    if (left < right)
    {
        size_t mid = left + (right - left) / 2;
        merge_sort_helper(base, left, mid, size, compar);
        merge_sort_helper(base, mid + 1, right, size, compar);
        merge(base, left, mid, right, size, compar);
    }
    return;
}

void merge_sort(void *base, size_t nitems, size_t size, int(*compar)(const void*, const void*))
{
    merge_sort_helper(base, 0, nitems - 1, size, compar);
    return;
}

void swap(void *a, void *b, size_t size) 
{
    char *temp = malloc(size);
    if (temp == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

static void three_way_partition(void *base, size_t low, size_t high, size_t size, int (*compar)(const void*, const void*), size_t *lt, size_t *gt) 
{
    void *pivot = malloc(size);
    if (!pivot) 
    {
        fprintf(stderr, "Memory allocation failed for pivot\n");
        exit(EXIT_FAILURE);
    }
    memcpy(pivot, (char *)base + low * size, size);

    size_t i = low;
    *lt = low;
    *gt = high;

    while (i <= *gt) 
    {
        int cmp = compar((char *)base + i * size, pivot);
        if (cmp < 0) 
        {
            swap((char *)base + (*lt) * size, (char *)base + i * size, size);
            (*lt)++;
            i++;
        } 
        else if (cmp > 0) 
        {
            swap((char *)base + i * size, (char *)base + (*gt) * size, size);
            (*gt)--;
        } 
        else 
        {
            i++;
        }
    }

    free(pivot);
}

void heapify(void *base, size_t n, size_t i, size_t size, int (*compar)(const void*, const void*)) 
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && compar((char *)base + left * size, (char *)base + largest * size) > 0)
        largest = left;

    if (right < n && compar((char *)base + right * size, (char *)base + largest * size) > 0)
        largest = right;

    if (largest != i) 
    {
        swap((char *)base + i * size, (char *)base + largest * size, size);
        heapify(base, n, largest, size, compar);
    }
}

void heap_sort(void *base, size_t n, size_t size, int (*compar)(const void*, const void*)) 
{
    for (size_t i = n / 2 - 1; i < n; i--)
        heapify(base, n, i, size, compar);

    for (size_t i = n - 1; i > 0; i--) {
        swap((char *)base, (char *)base + i * size, size);
        heapify(base, i, 0, size, compar);
    }
}

static void quick_sort_three_way(void *base, size_t low, size_t high, size_t size, int (*compar)(const void*, const void*), int depth_limit) 
{
    if (low < high) 
    {
        if (depth_limit == 0) 
        {
            fprintf(stderr, "Exceeded maximum recursion depth. Switching to heap sort.\n");
            heap_sort((char *)base + low * size, high - low + 1, size, compar);
            return;
        }

        size_t lt, gt;
        three_way_partition(base, low, high, size, compar, &lt, &gt);

        if (lt > 0)
        {
            quick_sort_three_way(base, low, lt - 1, size, compar, depth_limit - 1);
        }
        else
        {
            quick_sort_three_way(base, low, 0, size, compar, depth_limit - 1);
        }
        quick_sort_three_way(base, gt + 1, high, size, compar, depth_limit - 1);
    }
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{
    int max_depth = 3 * (int)(log(nitems) / log(2));
    quick_sort_three_way(base, 0, nitems - 1, size, compar, max_depth);
}

int compare_field1(const void *a, const void *b)
{
    return strcmp(((Record *)a)->field1, ((Record *)b)->field1);
}

int compare_field2(const void *a, const void *b)
{
    return ((Record *)a)->field2 - ((Record *)b)->field2;
}

int compare_field3(const void *a, const void *b)
{
    if (((Record *)a)->field3 < ((Record *)b)->field3) return -1;
    if (((Record *)a)->field3 > ((Record *)b)->field3) return 1;
    return 0;
}

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) 
{
    size_t capacity = 1000000;  
    Record *records = malloc(capacity * sizeof(Record));
    if (!records) 
    {
        fprintf(stderr, "Initial memory allocation failed\n");
        return;
    }

    int temp_id = 0;
    char temp_field1[100] = "";  
    int temp_field2 = 0;
    float temp_field3 = 0.0;
    size_t n = 0;

    while (fscanf(infile, "%d,%99[^,],%d,%f", &temp_id, temp_field1, &temp_field2, &temp_field3) == 4) 
    {
        records[n].id = temp_id;
        records[n].field1 = malloc(strlen(temp_field1) + 1);
        if (!records[n].field1) 
        {
            fprintf(stderr, "Memory allocation for field1 failed\n");
            for (size_t i = 0; i < n; i++) 
            {
                free(records[i].field1);
            }
            free(records);
            return; 
        }
        strcpy(records[n].field1, temp_field1);
        records[n].field2 = temp_field2;
        records[n].field3 = temp_field3;

        n++;
        if (n >= capacity) 
        {
            capacity *= 2;
            Record *temp_records = realloc(records, capacity * sizeof(Record));
            if (!temp_records) 
            {
                fprintf(stderr, "Memory reallocation failed at %zu records\n", n);
                for (size_t i = 0; i < n; i++) 
                {
                    free(records[i].field1);
                }
                free(records);
                return;
            }
            records = temp_records;
        }
    }

    int (*compar)(const void *, const void *) = NULL;
    switch (field) 
    {
        case 1:
            compar = compare_field1;
            break;
        case 2:
            compar = compare_field2;
            break;
        case 3:
            compar = compare_field3;
            break;
        default:
            fprintf(stderr, "Invalid field\n");
            for (size_t i = 0; i < n; i++) 
            {
                free(records[i].field1);
            }
            free(records);
            return;
    }

    if (algo == 1) 
    {
        merge_sort(records, n, sizeof(Record), compar);
    } 
    else if (algo == 2) 
    {
        quick_sort(records, n, sizeof(Record), compar);
    } 
    else 
    {
        fprintf(stderr, "Invalid algorithm\n");
        for (size_t i = 0; i < n; i++) 
        {
            free(records[i].field1);
        }
        free(records);
        return;
    }

    for (size_t i = 0; i < n; i++) 
    {
        fprintf(outfile, "%d,%s,%d,%.2f\n", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }

    for (size_t i = 0; i < n; i++) 
    {
        free(records[i].field1);
    }
    free(records);
} 
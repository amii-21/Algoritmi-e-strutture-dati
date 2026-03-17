#include "../src/sorting/sorting.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void setUp(void) {
    // Setup code (se necessario)
}

void tearDown(void) {
    // Teardown code (se necessario)
}


int compare_ints(const void *a, const void*b)
{
    return(*(int*)a - *(int*)b);
}

int compare_floats(const void *a, const void *b)
{
    float diff = (*(float*)a - *(float*)b);
    if (diff < 0)
    {
        return -1;
    }
    else if (diff > 0)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char**)a, *(const char**)b);
}

void test_int_sort()
{
    int arr[] = {5, 3, 8, 4, 2};
    int expected[] = {2, 3, 4, 5, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, n, sizeof(int), compare_ints);
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("test_int_sort with merge_sort passed.\n");

    int arr2[] = {5, 3, 8, 4, 2};
    quick_sort(arr2, n, sizeof(int), compare_ints);
    assert(memcmp(arr2, expected, sizeof(arr2)) == 0);
    printf("test_int_sort with quick_sort passed.\n");
    return;
}

void test_float_sort()
{
    float arr[] = {5.2, 3.1, 8.6, 4.3, 2.8};
    float expected[] = {2.8, 3.1, 4.3, 5.2, 8.6};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, n, sizeof(float), compare_floats);
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("test_float_sort with merge_sort passed.\n");

    float arr2[] = {5.2, 3.1, 8.6, 4.3, 2.8};
    quick_sort(arr2, n, sizeof(float), compare_floats);
    assert(memcmp(arr2, expected, sizeof(arr2)) == 0);
    printf("test_float_sort with quick_sort passed.\n");
    return;
}

void test_string_sort()
{
    const char *arr[] = {"apple", "orange", "banana", "grape", "cherry"};
    const char *expected[] = {"apple", "banana", "cherry", "grape", "orange"};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, n, sizeof(char*), compare_strings);
    assert(memcmp(arr, expected, sizeof(arr)) == 0);
    printf("test_string_sort with merge_sort passed.\n");

    const char *arr2[] = {"apple", "orange", "banana", "grape", "cherry"};
    quick_sort(arr2, n, sizeof(char*), compare_strings);
    assert(memcmp(arr2, expected, sizeof(arr2)) == 0);
    printf("test_string_sort with quick_sort passed.\n");
    return;
}

int main()
{
    test_int_sort();
    test_float_sort();
    test_string_sort();
    printf("All tests passed successfully.\n");
    return 0;
} 
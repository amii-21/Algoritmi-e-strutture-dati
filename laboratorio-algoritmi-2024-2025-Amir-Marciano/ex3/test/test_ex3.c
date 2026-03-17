#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hash_table.h"

unsigned long hash_string(const void* key) {
    const char* str = key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int compare_string(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

void test_insert_and_get() {
    HashTable* table = hash_table_create(compare_string, hash_string);

    char* key1 = strdup("apple");
    int* val1 = malloc(sizeof(int));
    *val1 = 10;
    hash_table_put(table, key1, val1);

    int* res = hash_table_get(table, "apple");
    assert(res && *res == 10);

    hash_table_free(table);
}

void test_overwrite() {
    HashTable* table = hash_table_create(compare_string, hash_string);

    char* key = strdup("banana");
    int* val1 = malloc(sizeof(int));
    *val1 = 1;
    hash_table_put(table, key, val1);

    int* val2 = malloc(sizeof(int));
    *val2 = 2;
    hash_table_put(table, strdup("banana"), val2); // Overwrite

    int* res = hash_table_get(table, "banana");
    assert(res && *res == 2);

    hash_table_free(table);
}

void test_remove() {
    HashTable* table = hash_table_create(compare_string, hash_string);

    char* key = strdup("kiwi");
    int* val = malloc(sizeof(int));
    *val = 5;
    hash_table_put(table, key, val);

    assert(hash_table_contains_key(table, "kiwi"));
    hash_table_remove(table, "kiwi");
    assert(!hash_table_contains_key(table, "kiwi"));

    hash_table_free(table);
}

void test_keyset() {
    HashTable* table = hash_table_create(compare_string, hash_string);

    hash_table_put(table, strdup("a"), malloc(sizeof(int)));
    hash_table_put(table, strdup("b"), malloc(sizeof(int)));
    hash_table_put(table, strdup("c"), malloc(sizeof(int)));

    void** keys = hash_table_keyset(table);
    assert(keys);
    assert(hash_table_size(table) == 3);

    free(keys);
    hash_table_free(table);
}

int main() {
    test_insert_and_get();
    test_overwrite();
    test_remove();
    test_keyset();
    printf("All tests passed.\n");
    return 0;
}

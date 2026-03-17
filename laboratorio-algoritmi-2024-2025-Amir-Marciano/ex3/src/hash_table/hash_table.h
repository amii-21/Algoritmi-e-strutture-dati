#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

typedef struct HashTable HashTable;

HashTable* hash_table_create(int (*f1)(const void*,const void*), unsigned long (*f2)(const void*));

void hash_table_put(HashTable*, const void*, const void*);

void* hash_table_get(const HashTable*, const void*);

int hash_table_contains_key(const HashTable*, const void*);

void hash_table_remove(HashTable*, const void*);

size_t hash_table_size(const HashTable*);

void** hash_table_keyset(const HashTable*);

void hash_table_free(HashTable*);





#endif // HASH_TABLE_H
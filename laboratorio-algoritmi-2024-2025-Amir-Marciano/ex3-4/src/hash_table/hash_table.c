#include  "hash_table.h"
#include  <stdlib.h>
#include  <string.h>

#define INITIAL_BUCKET_COUNT 101

typedef struct HashNode {
    void* key;
    void* value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** buckets;
    size_t bucket_count;
    int (*compare)(const void*, const void*);
    unsigned long (*hash)(const void*);
    size_t size;
} HashTable;

// Function to create a new hash node
static HashNode* hash_node_create(void* key, void* value) {
    HashNode* node = malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

// Function to create a new hash table
HashTable* hash_table_create(int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
    HashTable* table = malloc(sizeof(HashTable));
    table->bucket_count = INITIAL_BUCKET_COUNT;
    table->buckets = calloc(table->bucket_count, sizeof(HashNode*));
    table->compare = compare;
    table->hash = hash;
    table->size = 0;
    return table;
}

// Function to put a key-value pair into the hash table
void hash_table_put(HashTable* table, const void* key, const void* value) {
    size_t index = table->hash(key) % table->bucket_count;
    HashNode* node = table->buckets[index];

    while (node) {
        if (table->compare(key, node->key) == 0) {
            node->value = (void*)value;
            return;
        }
        node = node->next;
    }

    HashNode* new_node = hash_node_create((void*)key, (void*)value);
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->size++;
}

// Function to get a value by key from the hash table
void* hash_table_get(const HashTable* table, const void* key) {
    size_t index = table->hash(key) % table->bucket_count;
    HashNode* node = table->buckets[index];

    while (node) {
        if (table->compare(key, node->key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

// Function to check if a key exists in the hash table
int hash_table_contains_key(const HashTable* table, const void* key) {
    return hash_table_get(table, key) != NULL;
}

// Function to remove a key-value pair from the hash table
void hash_table_remove(HashTable* table, const void* key) {
    size_t index = table->hash(key) % table->bucket_count;
    HashNode* node = table->buckets[index];
    HashNode* prev = NULL;

    while (node) {
        if (table->compare(key, node->key) == 0) {
            if (prev)
                prev->next = node->next;
            else
                table->buckets[index] = node->next;

            free(node);
            table->size--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Function to get the size of the hash table
size_t hash_table_size(const HashTable* table) {
    return table->size;
}

// Function to get all keys from the hash table
void** hash_table_keyset(const HashTable* table) {
    void** keys = malloc(sizeof(void*) * table->size);
    size_t k = 0;
    for (size_t i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            keys[k++] = node->key;
            node = node->next;
        }
    }
    return keys;
}

// Function to free the hash table
void hash_table_free(HashTable* table) {
    for (size_t i = 0; i < table->bucket_count; i++) {
        HashNode* node = table->buckets[i];
        while (node) {
            HashNode* next = node->next;
            free(node);
            node = next;
        }
    }
    free(table->buckets);
    free(table);
}
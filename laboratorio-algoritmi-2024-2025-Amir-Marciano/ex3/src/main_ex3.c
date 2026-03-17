#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_table.h"

#define MAX_WORD_LEN 128

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

// Function to convert a string to lowercase
char* strdup_lower(const char* str) {
    size_t len = strlen(str);
    char* copy = malloc(len + 1);
    for (size_t i = 0; i < len; i++) {
        copy[i] = tolower((unsigned char)str[i]);
    }
    copy[len] = '\0';
    return copy;
}

// Function to process the file and count word frequencies
void process_file(HashTable* table, const char* filename, size_t min_length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LEN];
    while (fscanf(file, "%127s", word) == 1) {
        char cleaned[MAX_WORD_LEN];
        int j = 0;
        for (int i = 0; word[i] && j < MAX_WORD_LEN - 1; i++) {
            if (isalpha((unsigned char)word[i])) {
                cleaned[j++] = word[i];
            }
        }
        cleaned[j] = '\0';

        if (strlen(cleaned) < min_length)
            continue;

        char* key = strdup_lower(cleaned);
        int* count = hash_table_get(table, key);
        if (count) {
            (*count)++;
            free(key); 
        } else {
            int* new_count = malloc(sizeof(int));
            *new_count = 1;
            hash_table_put(table, key, new_count);
        }
    }

    fclose(file);
}

// Function to find and print the most frequent word
void find_most_frequent(const HashTable* table) {
    void** keys = hash_table_keyset(table); 
    size_t size = hash_table_size(table); 

    const char* max_word = NULL;
    int max_count = 0;

    for (size_t i = 0; i < size; i++) {
        const char* word = keys[i];
        int* count = hash_table_get(table, word);
        if (*count > max_count) {
            max_count = *count;
            max_word = word;
        }
    }

    if (max_word)
        printf("Most frequent word: '%s' (%d times)\n", max_word, max_count);

    free(keys);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file> <min_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];
    size_t min_length = (size_t)atoi(argv[2]);

    HashTable* table = hash_table_create(compare_string, hash_string);
    process_file(table, filename, min_length);

    if (hash_table_size(table) == 0) {
        printf("No words of at least %zu characters were found in the file.\n", min_length);
        hash_table_free(table);
        return 0;
    }

    find_most_frequent(table);
    hash_table_free(table);

    return 0;
}
 
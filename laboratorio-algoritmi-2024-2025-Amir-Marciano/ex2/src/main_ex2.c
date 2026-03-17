#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/edit_distance/edit_distance.h"
#include <limits.h>
#include <ctype.h>
#include <time.h>
#define MAX_WORD_LEN 100  // Maximum word length


// Function to read words from a file and store them in an array
char **read_words(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int capacity = 10000;
    char **words = (char **)malloc(capacity * sizeof(char *));
    *count = 0;

    char buffer[MAX_WORD_LEN];
    while (fscanf(file, "%s", buffer) != EOF) {
        clean_word(buffer);

        if (*count >= capacity) {
            capacity *= 2;  
            words = (char **)realloc(words, capacity * sizeof(char *));
        }

        words[*count] = strdup(buffer);  
        clean_word(words[*count]);
        (*count)++;
    }

    fclose(file);
    return words;
}

// Function to free allocated memory for words
void free_words(char **words, int count) {
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dictionary.txt> <correctme.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    clock_t start_time = clock(); 

    int dict_count, correctme_count;
    char **dictionary = read_words(argv[1], &dict_count);
    char **correctme = read_words(argv[2], &correctme_count);

    int corrected_count = 0;
    int total_count = correctme_count;

    for (int i = 0; i < correctme_count; i++) {
        char *word_to_correct = correctme[i];
        int min_distance = INT_MAX; 
        char **closest_words = malloc(dict_count * sizeof(char *)); 
        int closest_count = 0; 

        for (int j = 0; j < dict_count; j++) { 
            int distance = edit_distance_dyn(word_to_correct, dictionary[j]); 
            if (distance < min_distance) { 
                min_distance = distance; 
                closest_count = 0; 
                closest_words[closest_count++] = dictionary[j]; 
            } else if (distance == min_distance) {
                closest_words[closest_count++] = dictionary[j];
            }
        }

        if (min_distance > 0) { 
            corrected_count++;
        }
    
        printf("%s (min distance: %d): ", word_to_correct, min_distance);

        for (int k = 0; k < closest_count; k++) { 
            printf("%s ", closest_words[k]);
        }
        printf("\n");

        free(closest_words);
    }

    clock_t end_time = clock(); 
    double exec_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nParole corrette: %d su %d totali.\n", corrected_count, total_count);
    fprintf(stdout, "Execution time: %.2f seconds\n", exec_time);

    free_words(dictionary, dict_count);
    free_words(correctme, correctme_count);

    return 0;
}

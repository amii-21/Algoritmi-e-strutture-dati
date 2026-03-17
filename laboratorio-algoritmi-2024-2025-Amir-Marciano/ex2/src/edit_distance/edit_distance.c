#include "edit_distance.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>


// Function to clean words by removing punctuation characters
// and converting to lowercase
void clean_word(char *word) {
    int j = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (isalpha((unsigned char)word[i])) {
            word[j++] = tolower((unsigned char)word[i]);
        }
    }
    word[j] = '\0';
}

// Function to calculate the edit distance between two strings
int edit_distance(const char *s1, const char *s2) {
    if (*s1 == '\0') {
        return (int)strlen(s2);
    } else {
        if (*s2 == '\0') {
            return (int)strlen(s1);
        } else {
            if (*s1 == *s2) {
                return edit_distance(s1 + 1, s2 + 1);
            } else {
                int cost_delete = 1 + edit_distance(s1 + 1, s2);
                int cost_insert = 1 + edit_distance(s1, s2 + 1);
                if (cost_delete < cost_insert) {
                    return cost_delete;
                } else {
                    return cost_insert;
                }
            }
        }
    }
}

// Dynamic programming implementation of edit distance
int edit_distance_dyn(const char *s1, const char *s2) {
    int n = (int)strlen(s1);
    int m = (int)strlen(s2);

    int **dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((m + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                int delete_cost = dp[i - 1][j] + 1;
                int insert_cost = dp[i][j - 1] + 1;
                if (delete_cost < insert_cost) {
                    dp[i][j] = delete_cost;
                } else {
                    dp[i][j] = insert_cost;
                }
            }
        }
    }

    int result = dp[n][m];
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

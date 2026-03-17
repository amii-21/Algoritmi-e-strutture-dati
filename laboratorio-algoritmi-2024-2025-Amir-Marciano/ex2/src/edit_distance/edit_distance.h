#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

int edit_distance(const char *s1, const char *s2);

// Dynamic version of the edit distance function
int edit_distance_dyn(const char *s1, const char *s2);

void clean_word(char *word);

#endif // EDIT_DISTANCE_H
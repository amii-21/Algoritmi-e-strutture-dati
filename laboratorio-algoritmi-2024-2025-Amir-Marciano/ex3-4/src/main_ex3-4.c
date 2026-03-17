#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash_table.h"
#include "../src/graph/graph.h"

unsigned long hash_function(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}


int compare_function(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

// Function to perform breadth-first visit on the graph
void **breadth_first_visit(Graph gr, void* start, int (*compare)(const void*, const void*), unsigned long (*hash)(const void*)) {
   if (! graph_contains_node(gr, start)) {
        return NULL;
    }
    HashTable* visited = hash_table_create(compare, hash);
    void **queue = malloc(sizeof(void*) * (graph_num_nodes(gr) +1));
    void *current;
    int i, head = 0, tail = 0;
    queue[tail] = start;
    tail++;
    hash_table_put(visited, start, start);
    while (head < tail) {
        current = queue[head];
        head++;
        void **neighbours = graph_get_neighbours(gr, current);
        for (i = 0; i < graph_num_neighbours(gr, current); i++) {
            void *adj= neighbours[i];
            if (!hash_table_contains_key(visited, adj)) {
                queue[tail] = adj;
                tail++;
                hash_table_put(visited, adj, adj);
            }
        }
        free(neighbours);
    }
    hash_table_free(visited);
    void **result = malloc(sizeof(void*) * (tail + 1));
    for (i = 0; i < tail; i++) {
        result[i] = queue[i];
    }
    result[tail] = NULL;
    free(queue);
    return result;
}

//function to read the graph from a file
Graph read_graph_from_file(char *fileIn, char *start) {
    (void) start; // to avoid unused parameter warning
    FILE *fp = fopen(fileIn, "r");
    if (!fp) return NULL;
    Graph gr = graph_create(0, 0,  &compare_function, &hash_function);
    char *node1, *node2, tmp1[50], tmp2[50], line[256];
    float label;
    while (fgets(line, sizeof(line), fp)){
        sscanf(line, "%[^,],%[^,], %f",tmp1,tmp2,&label);
        node1 = (char*) malloc(sizeof(char) * (strlen(tmp1) + 1));
        node2 = (char*) malloc(sizeof(char) * (strlen(tmp2) + 1));
        strcpy(node1, tmp1);
        strcpy(node2, tmp2);
        if (!graph_contains_node(gr, node1)) graph_add_node(gr, node1);
        if (!graph_contains_node(gr, node2)) graph_add_node(gr, node2);
        graph_add_edge(gr, node1, node2, NULL);
        if (!graph_contains_edge(gr, node1, node2)) 
            graph_num_nodes(gr);
    }
    
    fclose(fp);
    return gr;

}

// Function to write the graph nodes to a file
int write_graph_to_file(void **nodes , char *fileOut) {
    FILE *fp = fopen(fileOut, "w");
    int i;
    for(i= 0; nodes[i]; i++){
        fprintf(fp, "%s\n", (char*)nodes[i]);
    }

    fclose(fp);
    return i;

}

int main(int argc, char *argv[]) {
    clock_t start_time = clock();

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input_file> <start_node> <output>\n", argv[0]);
        return -1;
    }
    char *fileIn = argv[1];
    char *start = argv[2];
    char *fileOut = argv[3];
    
    Graph gr = read_graph_from_file(fileIn, start); 
    if (!gr) {
        fprintf(stderr, "Error reading graph from file\n");
        return -1;
    }

    void **result = breadth_first_visit(gr, start, &compare_function, &hash_function);

    if (result == NULL) {
    fprintf(stderr, "Errore: nodo di partenza '%s' non trovato nel grafo.\n", start);
    return 1; 
    }
    
    int count = write_graph_to_file(result, fileOut);
    printf("Written %d nodes\n", count);
    free(result);
    result = graph_get_nodes(gr);
    int nodesNum = graph_num_nodes(gr);
    graph_free(gr);
    for (int i = 0; i < nodesNum; i++) {
        free(result[i]);
    }

    clock_t end = clock();
    double timeTaken = (double)(end - start_time) / CLOCKS_PER_SEC;
    printf("Time taken by the program: %.21f seconds\n", timeTaken);

    return 0;


}



        



    

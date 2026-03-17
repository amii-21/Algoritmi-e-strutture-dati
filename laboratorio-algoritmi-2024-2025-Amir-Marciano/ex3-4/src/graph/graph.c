#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "hash_table.h"
#include <stdbool.h>

typedef struct graph {

    int labelled; //1 if the graph is labelled, 0 otherwise
    int directed; //1 if the graph is directed, 0 otherwise
    int(*compare) (const void*, const void*); // Function to compare two nodes, used for hash table operations
    unsigned long(*hash) (const void*); // Function to hash a node, used for hash table operations
    HashTable* nodes;// Hash table to store nodes and their adjacency lists
} *Graph;

// Function to create a new graph
Graph graph_create(int labelled, int directed, int (*compare)(const void*, const void*),unsigned long (*hash)(const void*)){
    if (!compare || !hash) {
        return NULL;
    }
    Graph new_graph = malloc(sizeof(struct graph));
    if (!new_graph) {
        return NULL;
    }
    new_graph->labelled = labelled;
    new_graph->directed = directed;
    new_graph->compare = compare;
    new_graph->hash = hash;
    new_graph->nodes = hash_table_create(compare, hash);
    return new_graph;
}

// Function to check if the graph is directed or labelled
int graph_is_directed(const Graph gr){
    if (!gr) {
        return -1;
    }
    return gr->directed;
}
// Function to check if the graph is labelled
int graph_is_labelled(const Graph gr){
    if (!gr) {
        return -1;
    }
    return gr->labelled;
}

// Function to add a node to the graph
int graph_add_node(Graph gr, const void* node){
    if (!gr || !node) {
        return -1;
    }
    if (hash_table_contains_key(gr->nodes, node)) {
        return 0; 
    }
    HashTable *adjNodes = hash_table_create(gr->compare, gr->hash);
    hash_table_put(gr->nodes, node, adjNodes);
    return 1; 
}           

// Function to add an edge between two nodes in the graph
int graph_add_edge(Graph gr, const void* node1, const void* node2, const void* label){
    if (!gr || !node1 || !node2) return -1;
    if (!hash_table_contains_key(gr->nodes, node1) || !hash_table_contains_key(gr->nodes, node2)) return 0;
    
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node1);
    if (hash_table_contains_key(srcAdjNodes, node2)) return 0;
    if (gr->labelled) {
        hash_table_put(srcAdjNodes, node2, (void*)label);
    } else {
        hash_table_put(srcAdjNodes, node2, NULL);
    }

    if (!gr->directed) {
        HashTable* destAdjNodes = hash_table_get(gr->nodes, node2);
        if (gr->labelled) {
            hash_table_put(destAdjNodes, node1, (void*)label);
        } else {
            hash_table_put(destAdjNodes, node1, NULL);
        }
    }

    return 1;
}   

// Function to check if a node exists in the graph
int graph_contains_node(const Graph gr, const void* node){
    if (!gr || !node) {
        return -1;
    }
    return hash_table_contains_key(gr->nodes, node);
}          

// Function to check if an edge exists between two nodes in the graph
int graph_contains_edge(const Graph gr, const void* node1, const void* node2){
    if (!gr || !node1 || !node2) {
        return -1;
    }
    if (!hash_table_contains_key(gr->nodes, node1)) {
        return 0;
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node1);
    return hash_table_contains_key(srcAdjNodes, node2);
}             

// Function to remove a node from the graph
int graph_remove_node(Graph gr, const void* node){
    if (!gr || !node) {
        return -1;
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node);
    if (!srcAdjNodes) {
        return 0; 
    }
    hash_table_free(srcAdjNodes);
    hash_table_remove(gr->nodes, node);
    void **keys = hash_table_keyset(gr->nodes);
    int nodeCount = hash_table_size(gr->nodes), i;
    for ( i = 0; i < nodeCount; i++) {
        HashTable* destAdjNodes = hash_table_get(gr->nodes, keys[i]);
        if (hash_table_contains_key(destAdjNodes, node)) {
            hash_table_remove(destAdjNodes, node);
        }
    }
    free(keys);
    return 1;  
}  

// Function to remove an edge between two nodes in the graph
int graph_remove_edge(Graph gr, const void* node1, const void* node2){
    if (!gr || !node1 || !node2) {
        return -1;
    }
    if (!hash_table_contains_key(gr->nodes, node1)) {
        return 0; 
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node1);
    if (!hash_table_contains_key(srcAdjNodes, node2)) {
        return 0; 
    }
    hash_table_remove(srcAdjNodes, node2);
    if (!gr->directed) {
        srcAdjNodes = hash_table_get(gr->nodes, node2); 
        hash_table_remove(srcAdjNodes, node1);
    }
    return 1;
} 

// Function to get the number of nodes in the graph
int graph_num_nodes(const Graph gr){
    if (!gr) {
        return -1;
    }
    return hash_table_size(gr->nodes);  
}

// Function to get the number of edges in the graph
int graph_num_edges(const Graph gr){
    if (!gr) {
        return -1;
    }
    HashTable *curr = NULL;
    void **keys = hash_table_keyset(gr->nodes);
    int nodeCount = hash_table_size(gr->nodes),count = 0, i;
    for (i = 0; i < nodeCount; i++) {
        curr = hash_table_get(gr->nodes, keys[i]);
        count += hash_table_size(curr);
    }
    if (!gr->directed) {
        count= count / 2; 
    }
    free(keys);
    return count;          
}                                              

// Function to get all nodes in the graph
void** graph_get_nodes(const Graph gr){
    if (!gr) {
        return NULL;
    }
    return hash_table_keyset(gr->nodes); 
}

// Function to get all edges in the graph
Edge** graph_get_edges(const Graph gr){
    if (!gr) {
        return NULL;
    }
    int edgeCount = graph_num_edges(gr), NodeCount = graph_num_nodes(gr), i, edgeIndex = 0;
    if (edgeCount == 0) {
        return NULL;
    }
    if (NodeCount == 0) {
        return NULL;
    }
    Edge **set = (Edge**)malloc(sizeof(Edge*) * edgeCount);
    if (!set) {
        return NULL;
    }
    void **keys = hash_table_keyset(gr->nodes);
    for (i = 0; i < NodeCount; i++) {
        HashTable* srcAdjNodes = hash_table_get(gr->nodes, keys[i]);
        void** destKeys = hash_table_keyset(srcAdjNodes);
        int currNum = hash_table_size(srcAdjNodes), j;
        for (j = 0; j < currNum; j++) {
            if(!gr->directed && gr->compare(destKeys[j], keys[i]) < 0){ continue; }
            Edge *new = (Edge*)malloc(sizeof(Edge));
            if (!new) {
                continue;
            }
            new->source = keys[i];
            new->dest = destKeys[j];
            new->label = gr->labelled ? hash_table_get(srcAdjNodes, destKeys[j]) : NULL;
            set[edgeIndex] = new;
            edgeIndex++;
        }
        free(destKeys);
    }
    free(keys);
    return set; 
}                                   

// Function to get the neighbours of a node in the graph
void** graph_get_neighbours(const Graph gr, const void* node){
    if (!gr || !node) {
        return NULL;
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node);
    return srcAdjNodes ? hash_table_keyset(srcAdjNodes) : NULL ; 
}

// Function to get the number of neighbours of a node in the graph
int graph_num_neighbours(const Graph gr, const void* node){
    if (!gr || !node) {
        return -1;
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node);
    return srcAdjNodes ? hash_table_size(srcAdjNodes) : -1;
}                   

// Function to get the label of an edge between two nodes in the graph
void* graph_get_label(const Graph gr, const void* node1, const void* node2){
    if (!gr || !node1 || !node2) {
        return NULL;
    }
    if (!gr ->labelled) {
        return NULL; 
    }
    if (!hash_table_contains_key(gr->nodes, node1) || !hash_table_contains_key(gr->nodes, node2)) {
        return NULL;
    }
    HashTable* srcAdjNodes = hash_table_get(gr->nodes, node1);
    return hash_table_get(srcAdjNodes, node2);
}       

// Function to free the graph and its resources
void graph_free(Graph gr){
    if (!gr) {
        return;
    }
    void **keys = hash_table_keyset(gr->nodes);
    int nodeCount = hash_table_size(gr->nodes);
    for (int i = 0; i < nodeCount; i++) {
        HashTable* srcAdjNodes = hash_table_get(gr->nodes, keys[i]);
        hash_table_free(srcAdjNodes);
    }
    free(keys);
    hash_table_free(gr->nodes);
    free(gr);
}
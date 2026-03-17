#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/graph/graph.h"
#include "hash_table.h"


int string_compare(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

unsigned long string_hash(const void* key) {
    const char* str = (const char*)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash;
}

void test_graph_creation() {
    Graph gr = graph_create(0, 0, string_compare, string_hash);
    if (!gr) {
        printf("Create function failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_is_directed() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    if (!graph_is_directed(gr)) {
        printf("Is directed function failed.\n");
        return;
    }

    graph_free(gr);

    gr = graph_create(1, 0, string_compare, string_hash);
    if (graph_is_directed(gr)) {
        printf("Is directed function failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_is_labelled() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    if (!graph_is_labelled(gr)) {
        printf("Is labelled function failed.\n");
        return;
    }

    graph_free(gr);

    gr = graph_create(0, 1, string_compare, string_hash);
    if (graph_is_labelled(gr)) {
        printf("Is labelled function failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_add_node() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    if (graph_add_node(gr, "A") != 1) {
        printf("Add node failed.\n");
    }

    graph_free(gr);
}

void test_graph_add_edge() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    if (graph_add_edge(gr, "A", "B", "label1") != 1) {
        printf("Add edge failed.\n");
    }
    graph_free(gr);
}

void test_graph_contains_node() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    if (!graph_contains_node(gr, "A")) {
        printf("Contains node failed.\n");
    }

    graph_free(gr);
}

void test_graph_contains_edge() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    if (!graph_contains_edge(gr, "A", "B")) {
        printf("Contains edge failed.\n");
    }

    graph_free(gr);
}

void test_graph_remove_node() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    if (graph_remove_node(gr, "A") != 1) {
        printf("Remove node failed.\n");
    }
    if (graph_contains_node(gr, "A")) {
        printf("Graph node wasn't removed.\n");
    }

    graph_free(gr);
}

void test_graph_remove_edge() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    if (graph_remove_edge(gr, "A", "B") != 1) {
        printf("Remove edge failed.\n");
    }
    if (graph_contains_edge(gr, "A", "B")) {
        printf("Graph edge wasn't removed.\n");
    }

    graph_free(gr);
}

void test_graph_num_nodes() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_node(gr, "C");
    if (graph_num_nodes(gr) != 3) {
        printf("Graph num nodes failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_num_edges() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    if (graph_num_edges(gr) != 1) {
        printf("Graph num edges failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_get_nodes() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_node(gr, "C");
    void** nodes = graph_get_nodes(gr);
    if (!nodes || strcmp((const char*)nodes[0], "A") != 0 || strcmp((const char*)nodes[1], "B") != 0 || strcmp((const char*)nodes[2], "C") != 0) {
        printf("Graph get nodes failed.\n");
        return;
    }

    free(nodes);
    graph_free(gr);
}

void test_graph_get_edges() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    Edge** edges = graph_get_edges(gr);
    if (!edges || strcmp((const char*)edges[0]->source, "A") != 0 || strcmp((const char*)edges[0]->dest, "B") != 0) {
        printf("Graph get edges failed..\n");
        return;
    }

    free(edges);
    graph_free(gr);
}
void test_new_get_edges() {
    Graph gr = graph_create(1, 1, string_compare, string_hash); // grafo diretto
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");

    Edge** edges = graph_get_edges(gr);
    int count = 0;
    while (edges && edges[count]) count++;

    if (count != 1) {
        printf("Graph get edges (directed) failed: expected 1 edge, got %d\n", count);
        return;
    }
   if (!edges || strcmp((const char*)edges[0]->source, "A") != 0 || strcmp((const char*)edges[0]->dest, "B") != 0) {
        printf("Graph get edges failed..\n");
        return;
    }


    free(edges);
    graph_free(gr);
}

void test_graph_get_neighbours() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    void** neighbours = graph_get_neighbours(gr, "A");
    if (!neighbours || strcmp((const char*)neighbours[0], "B") != 0) {
        printf("Graph Get neighbours failed.\n");
        return;
    }

    free(neighbours);
    graph_free(gr);
}

void test_graph_num_neighbours() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    if (graph_num_neighbours(gr, "A") != 1) {
        printf("Graph num neightbours failed.\n");
        return;
    }

    graph_free(gr);
}

void test_graph_get_label() {
    Graph gr = graph_create(1, 1, string_compare, string_hash);
    graph_add_node(gr, "A");
    graph_add_node(gr, "B");
    graph_add_edge(gr, "A", "B", "label1");
    void* label = graph_get_label(gr, "A", "B");
    if (!label || strcmp((const char*)label, "label1") != 0) {
        printf("Graph get label failed.\n");
        return;
    }
    
    graph_free(gr);
}

int main() {
    
    test_graph_creation();
    test_graph_is_directed();
    test_graph_is_labelled();
    test_graph_add_node();
    test_graph_add_edge();
    test_graph_contains_node();
    test_graph_contains_edge();
    test_graph_remove_node();
    test_graph_remove_edge();
    test_graph_num_nodes();
    test_graph_num_edges();
    test_graph_get_nodes();
    test_graph_get_edges();
    test_graph_get_neighbours();
    test_graph_num_neighbours();
    test_graph_get_label();
    test_new_get_edges();

    printf("All tests passed successfully.\n");
    return 0;
}

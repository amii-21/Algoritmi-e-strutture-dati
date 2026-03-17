CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc/hash_table

BIN_DIR = bin
SRC_DIR = src
TEST_DIR = test
UNITY_DIR = unity

HASH_SRC = $(SRC_DIR)/hash_table/hash_table.c
GRAPH_SRC = $(SRC_DIR)/graph/graph.c
MAIN_SRC = $(SRC_DIR)/main_ex3-4.c
TEST_SRC = $(TEST_DIR)/test_ex3-4.c
UNITY_SRC = $(UNITY_DIR)/unity.c

all: $(BIN_DIR)/main_ex3-4 $(BIN_DIR)/test_ex3-4

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main_ex3-4: $(MAIN_SRC) $(GRAPH_SRC) $(HASH_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SRC) $(GRAPH_SRC) $(HASH_SRC)

$(BIN_DIR)/test_ex3-4: $(TEST_SRC) $(GRAPH_SRC) $(HASH_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC) $(GRAPH_SRC) $(HASH_SRC)

clean:
	rm -rf $(BIN_DIR) output.txt

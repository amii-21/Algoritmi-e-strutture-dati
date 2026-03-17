CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc/hash_table

BIN_DIR = bin
SRC_DIR = src
TEST_DIR = test
UNITY_DIR = unity

HASH_SRC = $(SRC_DIR)/hash_table/hash_table.c
MAIN_SRC = $(SRC_DIR)/main_ex3.c
TEST_SRC = $(TEST_DIR)/test_ex3.c
UNITY_SRC = $(UNITY_DIR)/unity.c

all: $(BIN_DIR)/main_ex3 $(BIN_DIR)/test_ex3

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main_ex3: $(MAIN_SRC) $(HASH_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SRC) $(HASH_SRC)

$(BIN_DIR)/test_ex3: $(TEST_SRC) $(HASH_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC) $(HASH_SRC)

clean:
	rm -rf $(BIN_DIR)

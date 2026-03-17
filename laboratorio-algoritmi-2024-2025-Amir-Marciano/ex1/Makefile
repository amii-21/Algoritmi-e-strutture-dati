CC = gcc
CFLAGS = -Wall -g

# Directory
SRC_DIR = src
SORTING_DIR = $(SRC_DIR)/sorting
UNITY_DIR = unity
TEST_DIR = test
BIN_DIR = bin

# File sorgente
SORTING_SRC = $(SORTING_DIR)/sorting.c
MAIN_SRC = $(SRC_DIR)/main_ex1.c
TEST_SRC = $(TEST_DIR)/test_ex1.c
UNITY_SRC = $(UNITY_DIR)/unity.c

# Eseguibili
MAIN_EXE = $(BIN_DIR)/main_ex1
TEST_EXE = $(BIN_DIR)/test_ex1

all: $(MAIN_EXE) $(TEST_EXE)

$(MAIN_EXE): $(MAIN_SRC) $(SORTING_SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(SORTING_DIR) -o $@ $(MAIN_SRC) $(SORTING_SRC)

$(TEST_EXE): $(TEST_SRC) $(SORTING_SRC) $(UNITY_SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(SORTING_DIR) -I$(UNITY_DIR) -o $@ $(TEST_SRC) $(SORTING_SRC) $(UNITY_SRC)

clean:
	rm -f $(MAIN_EXE) $(TEST_EXE)
	rm -rf $(BIN_DIR)/*.dSYM

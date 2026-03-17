CC = gcc
CFLAGS = -Wall -Wextra -g -I./unity

BIN_DIR = bin
SRC_DIR = src
TEST_DIR = test
UNITY_DIR = unity

EDIT_SRC = $(SRC_DIR)/edit_distance/edit_distance.c
MAIN_SRC = $(SRC_DIR)/main_ex2.c
TEST_SRC = $(TEST_DIR)/test_ex2.c
UNITY_SRC = $(UNITY_DIR)/unity.c

all: $(BIN_DIR)/main_ex2 $(BIN_DIR)/test_ex2

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/main_ex2: $(MAIN_SRC) $(EDIT_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SRC) $(EDIT_SRC)

$(BIN_DIR)/test_ex2: $(TEST_SRC) $(EDIT_SRC) $(UNITY_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC) $(EDIT_SRC) $(UNITY_SRC)

clean:
	rm -rf $(BIN_DIR)

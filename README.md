# Algorithms & Data Structures

Four exercises on core algorithms and data structures, implemented in C and C++ with unit tests and benchmarks.

---

## Exercise 1 — Sorting (Merge Sort & Quick Sort)

Generic sorting on arrays of arbitrary type. Benchmarked on datasets of up to 20 million records.

**Usage**
```bash
make all
./bin/main_ex1 records.csv sorted.csv <field> <algo>
```

- `field`: `1` = string, `2` = int, `3` = float  
- `algo`: `1` = MergeSort, `2` = QuickSort

---

## Exercise 2 — Edit Distance (spell checker)

Custom edit distance (insertions and deletions only) between two strings. Used to correct a text file by comparing each word against a dictionary.

**Files**
- `correctme.txt` — text to correct
- `dictionary.txt` — reference dictionary

**Usage**
```bash
make all
./bin/main_ex2 dictionary.txt correctme.txt
```

---

## Exercise 3 — Generic Hash Table

Hash table with chaining, implemented as a generic container in C.

**Usage**
```bash
make all
./bin/main_ex3 ./data/iliade.txt 6
```

**Tests**
```bash
./bin/test_ex3
```

---

## Exercise 4 — Sparse Graph + BFS

Sparse graph (adjacency list) with BFS traversal. Applied to a real dataset of distances between Italian cities. Reads the graph from `italian_dist_graph.csv`, runs BFS from a given city, and writes the visit order to an output file.

**Usage**
```bash
make all
./bin/main_ex3-4 ./data/italian_dist_graph.csv torino output.txt
```

**Tests**
```bash
./bin/test_ex3-4
```

---

## Stack

- C / C++
- Makefile
- Unit testing

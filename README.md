# C Data Structures Implementation

Implementation of classic data structures and algorithms in C, with a focus on clean APIs, modular design, and testable code.  
The project includes linked lists, stacks, AVL trees, hash tables, recursion utilities, and sorting algorithms.

---

## 📁 Project Structure

```text
.
├── bin
│   ├── debug/        # Debug builds of the executables
│   └── release/      # Release artifacts / placeholders
├── include/          # Public headers for all modules
├── lib/              # Static libraries (.a)
├── src/              # Data structure and algorithm implementations
└── test/             # Test programs for each module
```

## 🔧 Modules

**AVL Tree**
- Files: `avl.c`, `avl.h`, `avl_test.c`
- Self-balancing binary search tree with efficient insert/search/delete.

**C Hash Table**
- Files: `c_hash_table.c`, `c_hash_table.h`, `c_hash_table_test.c`
- Hash table implementation in C with separate chaining / buckets.

**Singly Linked List**
- Files: `singly_linked_list.c`, `singly_linked_list.h`, `singly_linked_list_test.c`
- Basic list operations: insert, delete, traverse, search.

**Doubly Linked List**
- Files: `doubly_linked_list.c`, `doubly_linked_list.h`, `libdoubly_linked_list.a`
- Bidirectional list implementation with a static library.

**Stack**
- Files: `stack.c`, `stack.h`, `stack_test.c`
- LIFO stack implementation and tests.

**Recursion Functions**
- Files: `recursion_funcs.c`, `recursion_funcs.h`, `recursion_funcs_test.c`, `librecursion.a`
- Classic recursion exercises (factorial, Fibonacci, etc.) as a reusable library.

**Sorting Algorithms**
- Files: `sorts.c`, `sorts.h`, `sorts_test.c`
- Implementations of common sorting algorithms (e.g., bubble, insertion, quick, merge – depending on implementation).

## 🧪 Building & Running

You can build the project either with a Makefile (if provided) or directly with `gcc`.

**Example: compile and run a test**
```bash
# Compile a specific test (e.g., stack)
gcc -Iinclude src/stack.c test/stack_test.c -o bin/debug/stack.out
```
## Run
./bin/debug/stack.out
Or use your preferred build system / IDE and link against the static libraries in `lib/`.

## 🎯 Goals
- Practice implementing core data structures in C
- Improve understanding of memory management and pointers
- Build a reusable base for future C projects and interview prep


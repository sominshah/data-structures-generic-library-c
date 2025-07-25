# Binary Search Tree (BST)

A **generic**, **self-contained**, and **memory-safe** Binary Search Tree implementation in C. Supports any data type via `void*`, with custom comparison and cleanup functions.

---

## 🔧 Features

* **Generic Node Storage**: Holds `void*` data
* **Custom Comparator**: User-defined `ComparatorFunctionBST` for ordering
* **Optional Cleanup**: User-defined `FreeFunctionBST` for deallocating node data
* **Core Operations**:

  * `add`       — Insert data into the tree
  * `remove`    — Delete a node by key, returning its data
  * `find`      — Search for a key
  * `isEmpty`   — Check if tree is empty
  * `getSize`   — Number of nodes
  * `clear`     — Remove all nodes (preserve tree structure)
  * `destroy`   — Free entire tree (including node data)
  * `getHeight` — Depth of the tree
* **Traversals**:

  * `inOrder`   — Left → Root → Right (sorted order)
  * `preOrder`  — Root → Left → Right
  * `postOrder` — Left → Right → Root
  * `levelOrder`— Breadth-first (using queue)

---

## 📖 Usage Example

```c
#include "binarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>

// Comparator for integers
int intComparator(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

// Print function
void printInt(void *data) {
    printf("%d ", *(int *)data);
}

int main() {
    // Create BST with default free() for node data
    BinarySearchTree *tree = bst_createBST(intComparator);

    // Insert values
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) {
        int *val = malloc(sizeof(int));
        *val = values[i];
        tree->add(tree, val);
    }

    // In-order traversal (sorted)
    printf("InOrder: ");
    tree->inOrder(tree, printInt);
    printf("\n");

    // Search for a key
    int key = 30;
    int *found = tree->find(tree, &key);
    printf("Find %d: %s\n", key, found ? "Found" : "Not Found");

    // Cleanup
    tree->destroy(tree);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**. Feel free to use, modify, and distribute.

---

## 🙌 Contributing

Pull requests and issues welcome! Consider adding:

* Deletion balancing (AVL/Red-Black)
* Iterative traversal methods
* Additional utility functions

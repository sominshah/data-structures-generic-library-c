# Generic Data Structure Library in C

A lightweight, **generic**, and **memory-safe** data structure library written in pure C. Supports any data type via `void*` and optional cleanup functions.

---

## 📚 Data Structures

| Data Structure     | Description                                                                                                                                                                   |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `SinglyList`       | Generic singly linked list with `listAdd`, `listGet`, `listRemoveAt`, `listSize`, `destroyList`, `getIterator`                                                                |
| `DoublyList`       | Doubly linked list with `addFirst`, `addLast`, `removeFirst`, `removeLast`, `removeAt`, `insertAt`, `listGet`, `listSize`, `destroyList`, `getIterator`, `getReverseIterator` |
| `Stack`            | LIFO stack with `push`, `pop`, `peek`, `destroy`, `isEmpty`, `getIterator`                                                                                                    |
| `Queue`            | FIFO queue with `enqueue`, `dequeue`, `peek`, `getSize`, `destroy`, `isEmpty`, `getIterator`                                                                                  |
| `Heap`             | Binary heap with `add`, `remove`, `peek`, `getSize`, `destroy`, `isEmpty`                                                                                                     |
| `BinarySearchTree` | BST with `add`, `remove`, `find`, `isEmpty`, `getSize`, `clear`, `destroy`, in-order/pre/post/level-order                                                                     |

---

## 🛠️ Folder Structure

```
datastructures/
├── include/                    # Public headers
│   └── datastructures.h        # Umbrella header
├── src/
│   ├── binarySearchTree/       # BST module
│   ├── doublyList/             # DoublyList module
│   ├── heap/                   # Heap module
│   ├── queue/                  # Queue module
│   ├── singlyList/             # SinglyList module
│   └── stack/                  # Stack module
├── lib/                        # Compiled libraries (.a / .so)
├── bin/                        # Test executables
```

---

## 🚀 Getting Started

### 1. Include Headers

```c
#include "datastructures.h"  // Or specific headers like "singlyList.h"
```

Ensure your compiler can locate `include/`.

### 2. Link the Library

**Static Linking:**

```bash
gcc -I ./datastructures/include ./main.c ./datastructures/lib/libraries.a -o app
```

**Shared Linking:**

```bash
gcc -I ./datastructures/include -L ./datastructures/lib main.c -llibraries -o app
```

### 3. Example: Using a Generic Int List

```c
#include "singlyList.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    SinglyList *list = SinglyList_createIntList();
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list->listAdd(list, val);
    }

    for (size_t i = 0; i < list->listSize(list); i++) {
        int *val = list->listGet(list, i);
        printf("Element %zu: %d\n", i, *val);
    }

    list->destroyList(list);
    return 0;
}
```

---

## 📜 License

This library is released under the **MIT License**.

---

## 🙌 Contributions Welcome

Feel free to fork, improve, and extend the library.
Upcoming modules:

* AVL Tree
* Common Algorithms

Pull requests and suggestions are always welcome!

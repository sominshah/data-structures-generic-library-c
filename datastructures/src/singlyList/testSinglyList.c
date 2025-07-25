# Singly Linked List

A **generic**, **memory-safe** singly linked list implementation in C. Supports any data type via `void*`, with custom cleanup and iterator support.

---

## 🔧 Features

* **Generic Storage**: Elements stored as `void*`
* **Custom Cleanup**: User-defined cleanup function (`FreeFunction`) to deallocate node data
* **Core Operations**:

  * `listAdd`      — Append data to the end of the list
  * `listGet`      — Retrieve data at a specific index
  * `listRemoveAt` — Remove node at a specific index
  * `listSize`     — Number of elements in the list
  * `destroyList`  — Free all nodes and list structure
* **Iterator Support**:

  * `getIterator` — Forward traversal starting at head
  * `SinglyListIterator` methods: `hasNext`, `next`, `destroy`

---

## 📁 API Overview

```c
// Create list with default cleanup
typedef void (*FreeFunction)(void *);
SinglyList *list = SinglyList_createList();  // uses free() by default

// Member methods
list->listAdd(list, data);
void *elem = list->listGet(list, index);
list->listRemoveAt(list, index);
size_t n = list->listSize(list);

// Iterator
SinglyListIterator *it = list->getIterator(list);
while (it->hasNext(it)) {
    void *d = it->next(it);
    // process d
}
it->destroy(it);

// Cleanup
list->destroyList(list);
```

* To customize cleanup, use:

  ```c
  SinglyList *list = SinglyList_new(freeFn);
  ```

  where `freeFn` is your own `void (*)(void*)` function.

---

## 📖 Usage Example

```c
#include "singlyList.h"
#include <stdio.h>
#include <stdlib.h>

// Custom cleanup for integers
void freeInt(void *data) {
    free(data);
}

int main() {
    // Create a list for integers
    SinglyList *list = SinglyList_new(freeInt);

    // Append values 0–4
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list->listAdd(list, val);
    }

    // Access by index
    for (size_t i = 0; i < list->listSize(list); i++) {
        int *v = list->listGet(list, i);
        printf("Element %zu: %d\n", i, *v);
    }

    // Iterate
    printf("\nIterating:\n");
    SinglyListIterator *it = list->getIterator(list);
    while (it->hasNext(it)) {
        int *v = it->next(it);
        printf("%d ", *v);
    }
    it->destroy(it);

    // Remove element at index 2
    int *removed = list->listGet(list, 2);
    list->listRemoveAt(list, 2);
    printf("\nRemoved at 2: %d\n", *removed);
    free(removed);

    // Cleanup all
    list->destroyList(list);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**. Feel free to use, modify, and distribute.

---

## 🙌 Contributing

Pull requests, issues, and feature suggestions are welcome.

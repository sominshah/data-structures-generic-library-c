#Doubly Linked List
A **generic**, **memory-safe** Doubly Linked List implementation in C. Supports any data type via `void*`, with custom cleanup functions.
---

## 🔧 Features

* **Bidirectional Links**: Each node has `prev` and `next` pointers
* **Custom Cleanup**: User-defined `FreeFunctionDoubly` for deallocating node data
* **Core Operations**:

  * `addFirst`        — Prepend data to the list
  * `addLast`         — Append data to the list
  * `removeFirst`     — Remove and return the first node’s data
  * `removeLast`      — Remove and return the last node’s data
  * `removeAt`        — Remove and return data at a specific index
  * `insertAt`        — Insert data at a specific index
  * `listGet`         — Retrieve data at a specific index
  * `listSize`        — Number of elements in the list
  * `clear`           — Remove all nodes (list remains usable)
  * `destroyList`     — Free the list structure and node data
* **Iterators**:

  * `getIterator`        — Forward traversal starting at head
  * `getReverseIterator` — Backward traversal starting at tail

---

## 📖 Usage Example

```c
#include "doublyList.h"
#include <stdio.h>
#include <stdlib.h>

// Cleanup for integers
void freeInt(void *data) {
    free(data);
}

int main() {
    // Create list with freeInt as cleanup
    DoublyList *list = DoublyList_createList();

    // Insert values at successive positions
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list->insertAt(list, i, val);
    }

    // Access by index
    for (size_t i = 0; i < list->listSize(list); i++) {
        int *val = list->listGet(list, i);
        printf("Element %zu: %d\n", i, *val);
    }

    // Forward iteration
    printf("\nForward iteration:\n");
    DoublyListIterator *it = list->getIterator(list);
    while (it->hasNext(it)) {
        int *v = it->next(it);
        printf("%d ", *v);
    }
    it->destroy(it);

    // Reverse iteration
    printf("\nReverse iteration:\n");
    DoublyListIterator *rit = list->getReverseIterator(list);
    while (rit->hasPrevious(rit)) {
        int *v = rit->previous(rit);
        printf("%d ", *v);
    }
    rit->destroy(rit);

    // Cleanup
    list->destroyList(list);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**. Feel free to use, modify, and distribute.

---

## 🙌 Contributing

Pull requests and issues welcome! Consider adding:

* Index-based access optimizations
* Bulk operations (split, merge)
* Iterator modification support

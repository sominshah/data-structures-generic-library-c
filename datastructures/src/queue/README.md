# Generic Queue

A **generic**, **memory-safe** FIFO queue implementation in C. Supports any data type via `void*`, with custom cleanup and iterator support.

---

## 🔧 Features

* **Generic Storage**: Elements stored as `void*` in a linked list
* **Custom Cleanup**: User-defined `FreeFunctionQueue` to deallocate element data
* **Core Operations**:

  * `enqueue`     — Add element to the tail
  * `dequeue`     — Remove and return element from the head
  * `peek`        — View the front element without removal
  * `getSize`     — Number of elements in the queue
  * `isEmpty`     — Check if queue is empty
  * `destroy`     — Free all elements and queue structure
* **Iterator Support**:

  * `getIterator` — Forward traversal over elements
  * `QueueIterator` methods: `hasNext`, `next`, `destroy`

---

## 📁 API Overview

```c
// Create a queue with default cleanup
Queue *queue = Queue_createQueue();

// Core methods
queue->enqueue(queue, data);
void *data = queue->dequeue(queue);
void *front = queue->peek(queue);
size_t size = queue->getSize(queue);
int empty = queue->isEmpty(queue);
queue->destroy(queue);

// Iterator
QueueIterator *it = queue->getIterator(queue);
while (it->hasNext(it)) {
    void *elem = it->next(it);
    // process elem
}
it->destroy(it);
```

* **`FreeFunctionQueue`** should free element memory (e.g., `free()`).

---

## 📖 Usage Example

```c
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Cleanup for integers
void freeInt(void *data) {
    free(data);
}

int main() {
    // Create queue
    Queue *queue = Queue_createQueue();

    // Enqueue 5 integers
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        queue->enqueue(queue, val);
    }

    // Print size
    printf("Queue Size: %zu\n", queue->getSize(queue));

    // Traverse via iterator
    printf("\nQueue elements (via iterator):\n");
    QueueIterator *it = queue->getIterator(queue);
    int idx = 0;
    while (it->hasNext(it)) {
        int *v = it->next(it);
        printf("Element at %d: %d\n", idx++, *v);
    }
    it->destroy(it);

    // Dequeue all and free
    printf("\nDequeueing elements:\n");
    while (!queue->isEmpty(queue)) {
        int *v = queue->dequeue(queue);
        printf("Removing: %d\n", *v);
        free(v);
    }

    // Final size
    printf("Queue Size after dequeue: %zu\n", queue->getSize(queue));

    // Cleanup queue
    queue->destroy(queue);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**. Feel free to use, modify, and distribute.

---

## 🙌 Contributing

Pull requests, issues, and suggestions are welcome. Consider adding:

* Indexed access support
* Bulk enqueue/dequeue operations
* Thread-safe variants


# Stack

A **generic**, **memory-safe** LIFO stack implementation in C. Supports any data type via `void*`, with custom cleanup and iterator support.

---

## 🔧 Features

* **Generic Storage**: Elements stored as `void*`
* **Custom Cleanup**: User-defined `FreeFunctionStack` to deallocate node data
* **Core Operations**:

  * `push`    — Add element to the top of the stack
  * `pop`     — Remove and return the top element
  * `peek`    — View the top element without removal
  * `getSize` — Number of elements in the stack
  * `isEmpty` — Check if stack is empty
  * `destroy` — Free all elements and stack structure
* **Iterator Support**:

  * `getIterator` — Forward traversal from top to bottom
  * `StackIterator` methods: `hasNext`, `next`, `destroy`

---

## 📁 API Overview

```c
// Create a stack with default cleanup
typedef void (*FreeFunctionStack)(void *);
Stack *stack = Stack_createStack();  // uses free() by default

// Member methods
stack->push(stack, data);
void *top = stack->peek(stack);
void *value = stack->pop(stack);
size_t n = stack->getSize(stack);
int empty = stack->isEmpty(stack);

// Iterator
StackIterator *it = stack->getIterator(stack);
while (it->hasNext(it)) {
    void *d = it->next(it);
    // process d
}
it->destroy(it);

// Cleanup
stack->destroy(stack);
```

* To customize cleanup, use:

  ```c
  Stack *stack = Stack_new(freeFn);
  ```

  where `freeFn` is your own `void (*)(void*)` function.

---

## 📖 Usage Example

```c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Custom cleanup for integers
void freeInt(void *data) {
    free(data);
}

int main() {
    // Create a stack for integers
    Stack *stack = Stack_new(freeInt);

    // Push values 0–4
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        stack->push(stack, val);
    }

    // Print size
    printf("Stack Size: %zu\n", stack->getSize(stack));

    // Iterate
    printf("\nIterating:\n");
    StackIterator *it = stack->getIterator(stack);
    while (it->hasNext(it)) {
        int *v = it->next(it);
        printf("%d ", *v);
    }
    it->destroy(it);

    // Pop all elements
    printf("\nPopping:\n");
    while (!stack->isEmpty(stack)) {
        int *v = stack->pop(stack);
        printf("Popped: %d\n", *v);
        free(v);
    }

    // Final size
    printf("Stack Size after pop: %zu\n", stack->getSize(stack));

    // Cleanup stack
    stack->destroy(stack);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**.

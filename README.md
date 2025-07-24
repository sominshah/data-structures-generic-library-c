# Generic Data Structure Library in C

This library provides a set of generic, easy-to-use, and memory-safe data structures written in pure C. It supports any data type using `void*` and allows optional memory management via user-defined cleanup functions.

---

## 📦 Features

* ✅ Generic Singly Linked List
* ✅ Optional cleanup functions (like `free()`) for memory safety
* ✅ Predefined list creators (int, float, double, char\*, etc.)
* ✅ Type-safe wrappers and user-friendly APIs
* ✅ Iterator support for easy traversal
* ✅ Stack, queue, and other structures coming soon

---

## 📚 Data Structures

| Data Structure | Description                                                      |
| -------------- | ---------------------------------------------------------------- |
| `SinglyList`   | Generic singly linked list with append, get, remove, clone, etc. |
| `Stack`        | Generic stack with push, pop, peek, clone, destroy, isEmpty etc. |

---

## 🚀 Getting Started

### 🛠 Folder Structure

```
datastructures/
├── include/              # Main header files
│   └── datastructures.h  # Aggregated include file
├── src/
│   ├── singlyList/       # Singly linked list implementation
│   └── stack/            # Stack implementation
├── lib/                  # Compiled static/shared libraries
├── bin/                  # Test executables
```

---

## 🚀 How to Use

You can **reuse this library in your own C projects** by linking against the prebuilt `.a` or `.so` files in the `lib/` directory.

### 🛠️ 1. Include headers

```c
#include "datastructures.h" // or include individual headers like singlyList.h
```

Make sure your compiler can find the `include/` directory.

---

### 📚 2. Link the static or shared library

If you have:

* Static lib: `datastructures/lib/libraries.a`
* Shared lib: `datastructures/lib/libraries.so`

#### ✅ Compile using gcc:

```sh
gcc -I ./datastructures/include -L ./datastructures/lib main.c -llibraries -o app
```

Or with static linking:

```sh
gcc -I ./datastructures/include ./main.c ./datastructures/lib/libraries.a -o app
```

---

### 📖 Example: Using a Generic Int List

```c
#include "singlyList.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    SinglyList *list = SinglyList_createIntList(); // Wrapper
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

## 🚫 License

This library is open-source and free to use under the MIT License.

---

## 🙌 Contributions Welcome

Feel free to fork, extend, and improve the library. Upcoming modules include:

* SinglyList Iterators
* Queue
* Min Heap
* Max Heap
* Tree

PRs and suggestions are always welcome!

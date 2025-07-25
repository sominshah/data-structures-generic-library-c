# Generic Heap

A **generic**, **memory-safe** binary heap implementation in C. Supports any data type via `void*`, with custom ordering and cleanup functions.

---

## 🔧 Features

* **Dynamic Array Storage**: Automatically resizes as elements are added
* **Min-Heap or Max-Heap**: Behavior defined by user-provided comparator
* **Custom Cleanup**: User-defined `FreeFunctionHeap` to deallocate element data
* **Core Operations**:

  * `add`     — Insert an element (heapify up)
  * `remove`  — Extract top element (heapify down)
  * `peek`    — View top element without removal
  * `getSize` — Number of elements in heap
  * `isEmpty` — Check if heap has no elements
  * `destroy` — Free all elements and heap structure

---

## 📁 API Overview

```c
// Allocate a heap with default cleanup and comparator
Heap *studentHeap = Heap_new(studentRelease, ageComparator);

// Core methods
void Heap_add(Heap *heap, void *data);
void *Heap_remove(Heap *heap);
void *Heap_peek(Heap *heap);
size_t Heap_getSize(Heap *heap);
int Heap_isEmpty(Heap *heap);
void Heap_destroy(Heap *heap);
```

* **`studentRelease`**: Frees a `Student*` (should free internal fields and struct).
* **`ageComparator`**: Returns negative/zero/positive to order students by age.

---

## 📖 Usage Example

```c
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a student struct
typedef struct Student {
    int rollNumber;
    int age;
    char gender;
    char *name;
    char *mobileNumber;
} Student;

// Comparator: max-heap by age
int ageComparator(void *a, void *b) {
    return ((Student *)b)->age - ((Student *)a)->age;
}

// Cleanup for Student*
void studentRelease(void *data) {
    Student *s = (Student *)data;
    free(s->name);
    free(s->mobileNumber);
    free(s);
}

// Helper to create a student
Student *createStudent(int id, int age, char gender,
                       const char *name, const char *mobile) {
    Student *s = malloc(sizeof(Student));
    s->rollNumber = id;
    s->age = age;
    s->gender = gender;
    s->name = strdup(name);
    s->mobileNumber = strdup(mobile);
    return s;
}

int main() {
    // Create a max-heap of Student*
    Heap *studentHeap = Heap_new(studentRelease, ageComparator);

    // Add students
    studentHeap->add(studentHeap, createStudent(101,21,'M',"Raju","+91835..."));
    studentHeap->add(studentHeap, createStudent(102,19,'F',"Priya","+91981..."));
    studentHeap->add(studentHeap, createStudent(103,23,'M',"Vikram","+91981..."));

    // Remove in descending age order
    printf("\nRemoving students by age:\n");
    while (!studentHeap->isEmpty(studentHeap)) {
        Student *s = studentHeap->remove(studentHeap);
        printf("%s (Age %d)\n", s->name, s->age);
    }

    studentHeap->destroy(studentHeap);
    return 0;
}
```

---

## 📜 License

Released under the **MIT License**. Feel free to use, modify, and distribute.

---

## 🙌 Contributing

Pull requests, issues, and suggestions are welcome. Consider adding:

* Bulk operations (build-heap in linear time)
* Heap sort utility
* Thread-safe extensions

 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-23
 * Description  : Singly Linked List
 
===========================
Generic Singly Linked List
===========================
This library provides a generic, flexible, and memory-safe singly linked list in C.
USAGE MODES
===========

1. Beginner Mode (No cleanup knowledge required)
------------------------------------------------
(a) For integers (auto cleanup)
    
    SinglyList *list = createIntList();

    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        listAdd(list, val);
    }

    destroyList(list);  // Safe cleanup

(b) For custom types (you handle memory)
    
    SinglyList *list = createSimpleList();

    char *str = strdup("Hello");
    listAdd(list, str);

    free(str);  // You are responsible for cleanup
    destroyList(list);  // Only frees nodes, not data


2. Advanced Mode (Provide custom cleanup)
-----------------------------------------
    
    void freeString(void *data) {
        free(data);
    }

    SinglyList *list = createList(freeString);
    
    char *msg = strdup("World");
    listAdd(list, msg);
    destroyList(list);  // Also calls freeString(msg)

FUNCTIONS
=========

- listAdd(list, data)      → Adds element to end
- listGet(list, index)     → Returns data at index
- listSize(list)           → Returns number of items
- destroyList(list)        → Cleans up all memory

SAFEGUARDS
==========

- If no `freeFn` is given, destroyList only frees internal nodes.
- If `freeFn` is provided, it will be applied to all `data` nodes on destruction.
- NULL checks are internally managed.


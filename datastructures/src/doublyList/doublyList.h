#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stddef.h> // for size_t
#ifdef __cplusplus
extern "C" {          //"These functions have C-style names, do not mangle them."
#endif
/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Doubly Linked List
 */

typedef void (*FreeFunctionDoubly)(void *);
typedef struct DoublyListNode {
    void *data;
    struct DoublyListNode *next;
    struct DoublyListNode *prev;
} DoublyListNode;


typedef struct DoublyListIterator {
    DoublyListNode *current;
    int (*hasPrevious)(struct DoublyListIterator *iterator);
    int (*hasNext)(struct DoublyListIterator *iterator);
    void * (*previous)(struct DoublyListIterator *iterator);
    void *(*next)(struct DoublyListIterator *iterator);
    void (*destroy)(struct DoublyListIterator *iterator);

} DoublyListIterator;


typedef struct DoublyList 
{
DoublyListNode *head;
DoublyListNode *tail;
size_t size;
FreeFunctionDoubly freeFn;        
void (*addFirst)(struct DoublyList *list, void *data);
void (*addLast)(struct DoublyList *list, void *data);
void * (*removeFirst)(struct DoublyList *list);
void * (*removeLast)(struct DoublyList *list);
void * (*removeAt)(struct DoublyList *list, size_t index);
void (*insertAt)(struct DoublyList *list, size_t index, void *data);
void * (*listGet)(struct DoublyList *list, size_t index);
size_t (*listSize)(struct DoublyList *list);
void (*destroyList)(struct DoublyList *list);
DoublyListIterator *(*getIterator)(struct DoublyList *);
DoublyListIterator *(*getReverseIterator)(struct DoublyList *);
} DoublyList;

DoublyListIterator *DoublyListIterator_new(DoublyListNode *start); 

void DoublyList_freeData(void *data);
DoublyList * DoublyList_createList();                 
DoublyList* DoublyList_new(FreeFunctionDoubly freeFn);

void DoublyList_addFirst(struct DoublyList *list, void *data);
void DoublyList_addLast(struct DoublyList *list, void *data);
void * DoublyList_removeFirst(struct DoublyList *list);
void * DoublyList_removeLast(struct DoublyList *list);
void * DoublyList_removeAt(struct DoublyList *list, size_t index);
void DoublyList_insertAt(DoublyList *list, size_t index, void *data);
void * DoublyList_listGet(struct DoublyList *list, size_t index);
size_t DoublyList_listSize(struct DoublyList *list);
void DoublyList_destroyList(struct DoublyList *list);

#ifdef __cplusplus
}
#endif

#endif
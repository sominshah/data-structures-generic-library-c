/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Doubly Linked List
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublyList.h"

typedef void (*FreeFunctionDoubly)(void *);


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




static DoublyListIterator *DoublyList_getIterator(DoublyList *list);
static DoublyListIterator *DoublyList_getReverseIterator(DoublyList *list);
static int DoublyListIterator_hasNext(DoublyListIterator *iterator); 
static int DoublyListIterator_hasPrevious(DoublyListIterator *iterator); 
static void *DoublyListIterator_next(DoublyListIterator *iterator); 
static void *DoublyListIterator_previous(DoublyListIterator *iterator); 
static void DoublyListIterator_destroy(DoublyListIterator *iterator); 
DoublyListIterator *DoublyListIterator_new(DoublyListNode *start); 




void DoublyList_freeData(void *data){free(data);}
DoublyList * DoublyList_createList(){

    return DoublyList_new(DoublyList_freeData);
}
DoublyList* DoublyList_new(FreeFunctionDoubly freeFn)
{
    DoublyList *list = (DoublyList *)malloc(sizeof(DoublyList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->freeFn = freeFn;
    list->addFirst = DoublyList_addFirst;
    list->addLast = DoublyList_addLast;
    list->removeFirst = DoublyList_removeFirst;
    list->removeLast = DoublyList_removeLast;
    list->removeAt = DoublyList_removeAt;
    list->insertAt = DoublyList_insertAt;
    list->listGet = DoublyList_listGet;
    list->listSize = DoublyList_listSize;
    list->destroyList = DoublyList_destroyList;
    list->getIterator = DoublyList_getIterator;
    list->getReverseIterator = DoublyList_getReverseIterator;    
    return list;
}

void DoublyList_addFirst(struct DoublyList *list, void *data)
{
    if (!list)return;
    DoublyListNode *node = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    node->data = data;
    node->prev = NULL;
    node->next = list->head;
    if (list->head)
        list->head->prev = node;
    else list->tail = node;
    list->head = node;
    list->size++;
}
void DoublyList_addLast(struct DoublyList *list, void *data)
{
    if(!list)return;
     DoublyListNode *node = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail) list->tail->next = node;
    else list->head = node;
    list->tail = node;
    list->size++;
}
void * DoublyList_removeFirst(struct DoublyList *list)
{
    if (!list || list->head == NULL) return NULL;
    DoublyListNode *node = list->head;
    void *data = node->data;
    list->head = node->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
    free(node);
    list->size--;
    return data;
}

void *DoublyList_removeLast(struct DoublyList *list) 
{
    if (!list || list->tail == NULL) return NULL;

    DoublyListNode *node = list->tail;
    void *data = node->data;

    list->tail = node->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;

    free(node);
    list->size--;

    return data;
}

void * DoublyList_removeAt(struct DoublyList *list, size_t index)
{
    if (!list || index >= list->size) return NULL;

    if (index == 0) return DoublyList_removeFirst(list);
    if (index == list->size - 1) return DoublyList_removeLast(list);

    DoublyListNode *current = list->head;
    for (size_t i = 0; i < index; i++) current = current->next;

    void *data = current->data;

    current->prev->next = current->next;
    current->next->prev = current->prev;

    free(current);
    list->size--;

    return data;
}

void DoublyList_insertAt(DoublyList *list, size_t index, void *data)
{

    if (!list || index > list->size) return;
    if (index == 0) {
        DoublyList_addFirst(list, data);
        return;
    }
    if (index == list->size) {
        DoublyList_addLast(list, data);
        return;
    }

    DoublyListNode *current = list->head;
    for (size_t i = 0; i < index; i++)
        current = current->next;

    DoublyListNode *node = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    node->data = data;
    node->prev = current->prev;
    node->next = current;

    current->prev->next = node;
    current->prev = node;

    list->size++;

}
void * DoublyList_listGet(struct DoublyList *list, size_t index)
{

   if (index >= list->size) return NULL;
    DoublyListNode *current = list->head;
    for (size_t i = 0; i < index; i++)
        current = current->next;
    return current->data;

}
size_t DoublyList_listSize(struct DoublyList *list)
{
  return list->size;
}
void DoublyList_destroyList(struct DoublyList *list)
{
        DoublyListNode *current = list->head;
    while (current) {
        DoublyListNode *next = current->next;
        if (list->freeFn) list->freeFn(current->data);
        free(current);
        current = next;
    }
    free(list);

}



static DoublyListIterator *DoublyList_getIterator(DoublyList *list)
{
    return DoublyListIterator_new(list->head);
}

static DoublyListIterator *DoublyList_getReverseIterator(DoublyList *list)
{
    return DoublyListIterator_new(list->tail);
}


static int DoublyListIterator_hasNext(DoublyListIterator *iterator) 
{
    return iterator->current != NULL;
}
static int DoublyListIterator_hasPrevious(DoublyListIterator *iterator) 
{
    return iterator->current != NULL;
}

static void *DoublyListIterator_next(DoublyListIterator *iterator) 
{
    if (!iterator->current) return NULL;
    void *data = iterator->current->data;
    iterator->current = iterator->current->next;
    return data;
}
static void *DoublyListIterator_previous(DoublyListIterator *iterator) 
{
    if (!iterator->current) return NULL;
    void *data = iterator->current->data;
    iterator->current = iterator->current->prev;
    return data;
}

static void DoublyListIterator_destroy(DoublyListIterator *iterator) 
{
    free(iterator);
}

DoublyListIterator *DoublyListIterator_new(DoublyListNode *start) 
{
    DoublyListIterator *iterator = malloc(sizeof(DoublyListIterator));
    if (!iterator) return NULL;
    iterator->current = start;
    iterator->hasNext = DoublyListIterator_hasNext;
    iterator->next = DoublyListIterator_next;
    iterator->previous=DoublyListIterator_previous;
    iterator->hasPrevious=DoublyListIterator_hasPrevious;
    iterator->destroy = DoublyListIterator_destroy;
    return iterator;
}

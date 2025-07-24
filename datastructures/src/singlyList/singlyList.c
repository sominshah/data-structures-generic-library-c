/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-23
 * Description  : Singly Linked List
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singlyList.h"

typedef void (*FreeFunction)(void *);
void SinglyList_freeInt(void *data);
void SinglyList_freeChar(void *data);
void SinglyList_freeFloat(void *data);
void SinglyList_freeDouble(void *data);
void SinglyList_freeString(void *data);

SinglyList * SinglyList_createIntList();                     
SinglyList * SinglyList_createCharList();
SinglyList * SinglyList_createFloatList();                     
SinglyList * SinglyList_createDoubleList();                    
SinglyList * SinglyList_createStringList();                    
SinglyList* SinglyList_new(FreeFunction freeFn);


SinglyList * SinglyList_cloneList(struct SinglyList *list,FreeFunction freeFn);
void SinglyList_listAdd(SinglyList *list, void *data);
void * SinglyList_listGet(SinglyList *list, size_t index);
void SinglyList_listRemoveAt(SinglyList *list, size_t index);
size_t SinglyList_listSize(SinglyList *list);
void SinglyList_destroyList(SinglyList *list);
static SinglyListIterator *SinglyList_getIterator(SinglyList *list);


//Ieterator function declarations
static int SinglyListIterator_hasNext(SinglyListIterator *iterator); 
static void *SinglyListIterator_next(SinglyListIterator *iterator); 
static void SinglyListIterator_destroy(SinglyListIterator *iterator); 
SinglyListIterator *SinglyListIterator_new(SinglyListNode *start); 




// ======= Internal Memory-Freeing Functions =======

void SinglyList_freeInt(void *data)   { free(data); }
void SinglyList_freeChar(void *data)  { free(data); }
void SinglyList_freeFloat(void *data) { free(data); }
void SinglyList_freeDouble(void *data){ free(data); }
void SinglyList_freeString(void *data){ free(data); }



SinglyList* SinglyList_createIntList()    { return SinglyList_new(SinglyList_freeInt); }

SinglyList* SinglyList_createCharList()   { return SinglyList_new(SinglyList_freeChar); }

SinglyList* SinglyList_createFloatList()  { return SinglyList_new(SinglyList_freeFloat); }

SinglyList* SinglyList_createDoubleList() { return SinglyList_new(SinglyList_freeDouble); }

SinglyList* SinglyList_createStringList() { return SinglyList_new(SinglyList_freeString); }

SinglyList* SinglyList_new(FreeFunction freeFn)
{
SinglyList * list=(SinglyList *) malloc(sizeof(SinglyList));
if(list==NULL)return NULL;
	
	list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->freeFn = freeFn;

    // Bind methods
    list->cloneList = SinglyList_cloneList;
    list->listAdd = SinglyList_listAdd;
    list->listGet = SinglyList_listGet;
    list->listRemoveAt = SinglyList_listRemoveAt;
    list->listSize = SinglyList_listSize;
    list->destroyList = SinglyList_destroyList; 
    list->getIterator = SinglyList_getIterator; 

    return list;
}

SinglyList * SinglyList_cloneList(SinglyList *list, FreeFunction freeFn) 
{
    if (!list) return NULL;

    SinglyList *clone = SinglyList_new(freeFn);
    if (!clone) return NULL;

    SinglyListNode *curr = list->head;
    while (curr) {
        void *dataCopy = malloc(sizeof(*(curr->data))); // Shallow copy
        if (dataCopy) memcpy(dataCopy, curr->data, sizeof(*(curr->data)));
        clone->listAdd(clone, dataCopy);
        curr = curr->next;
    }
    return clone;
}
void SinglyList_listAdd(SinglyList *list, void *data)
{
	if(!list)return;
	SinglyListNode * node = (SinglyListNode *) malloc(sizeof(SinglyListNode));
	if(!node)return;
	node->data=data;
	node->next=NULL;
	if(list->size==0)
	{
		list->head=node;
		list->tail=node;
	}else
	{
		list->tail->next=node;
		list->tail=node;
	}
	list->size++;
}

void * SinglyList_listGet(SinglyList *list, size_t index)
{
	  if (!list || index >= list->size) return NULL;
	
	    SinglyListNode *curr = list->head;
    	for (size_t i = 0; i < index; i++) {
        	curr = curr->next;
    	}
    return curr ? curr->data : NULL;
}

void SinglyList_listRemoveAt(SinglyList *list, size_t index)
{
	if (!list || index >= list->size) return;
    SinglyListNode *prev = NULL;
    SinglyListNode *curr = list->head;

    for (size_t i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) {
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    if (curr == list->tail) {
        list->tail = prev;
    }

    if (list->freeFn) list->freeFn(curr->data);
    free(curr);
    list->size--;
}
size_t SinglyList_listSize(SinglyList *list)
{
	  return list ? list->size : 0;
}
void SinglyList_destroyList(SinglyList *list)
{
	 if (!list) return;
    SinglyListNode *curr = list->head;
    while (curr) {
        SinglyListNode *next = curr->next;
        if (list->freeFn) list->freeFn(curr->data);
        free(curr);
        curr = next;
    }

    free(list);
}


static SinglyListIterator *SinglyList_getIterator(SinglyList *list)
{
    return SinglyListIterator_new(list->head);
}



//In C, static for functions means file-local visibility (not class-level, since C doesn't have classes
static int SinglyListIterator_hasNext(SinglyListIterator *iterator) 
{
    return iterator->current != NULL;
}

static void *SinglyListIterator_next(SinglyListIterator *iterator) 
{
    if (!iterator->current) return NULL;
    void *data = iterator->current->data;
    iterator->current = iterator->current->next;
    return data;
}

static void SinglyListIterator_destroy(SinglyListIterator *iterator) 
{
    free(iterator);
}

SinglyListIterator *SinglyListIterator_new(SinglyListNode *start) 
{
    SinglyListIterator *iterator = malloc(sizeof(SinglyListIterator));
    if (!iterator) return NULL;
    iterator->current = start;
    iterator->hasNext = SinglyListIterator_hasNext;
    iterator->next = SinglyListIterator_next;
    iterator->destroy = SinglyListIterator_destroy;
    return iterator;
}

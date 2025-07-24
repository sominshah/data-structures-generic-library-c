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
void SinglyList_freeData(void *data);

SinglyList * SinglyList_createList();                    
SinglyList* SinglyList_new(FreeFunction freeFn);

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


void SinglyList_freeData(void *data)   { free(data); }

SinglyList* SinglyList_createList()    { return SinglyList_new(SinglyList_freeData); }

SinglyList* SinglyList_new(FreeFunction freeFn)
{
SinglyList * list=(SinglyList *) malloc(sizeof(SinglyList));
if(list==NULL)return NULL;
	
	list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->freeFn = freeFn;

    // Bind methods
    list->listAdd = SinglyList_listAdd;
    list->listGet = SinglyList_listGet;
    list->listRemoveAt = SinglyList_listRemoveAt;
    list->listSize = SinglyList_listSize;
    list->destroyList = SinglyList_destroyList; 
    list->getIterator = SinglyList_getIterator; 
    return list;
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

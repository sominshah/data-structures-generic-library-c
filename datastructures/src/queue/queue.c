/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Queue
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef void (*FreeFunctionQueue)(void *);

void Queue_enqueue(Queue *queue, void *data);
void * Queue_dequeue(Queue *queue);
void * Queue_peek(Queue *queue);
size_t Queue_getSize(Queue *queue);
void Queue_destroy(Queue *queue);
int Queue_isEmpty(Queue *queue);
static QueueIterator * Queue_getIterator(struct Queue *);


static int QueueIterator_hasNext(QueueIterator *iterator); 
static void *QueueIterator_next(QueueIterator *iterator); 
static void QueueIterator_destroy(QueueIterator *iterator); 
QueueIterator *QueueIterator_new(QueueNode *start);


void Queue_freeData(void *data);
void Queue_freeData(void *data)   { free(data); }
Queue * Queue_createQueue();                     
Queue* Queue_new(FreeFunctionQueue freeFn);

Queue* Queue_createQueue()    { return Queue_new(Queue_freeData); }

Queue* Queue_new(FreeFunctionQueue freeFn)
{
Queue * queue=(Queue *) malloc(sizeof(Queue));
if(queue==NULL)return NULL;    
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->freeFn = freeFn;

    // Bind methods
    queue->enqueue = Queue_enqueue;
    queue->dequeue = Queue_dequeue;
    queue->peek = Queue_peek;
    queue->getSize = Queue_getSize;
    queue->destroy = Queue_destroy;
    queue->isEmpty=Queue_isEmpty;
    queue->getIterator = Queue_getIterator;
    return queue;
}


size_t Queue_getSize(Queue *queue)
{
	  return queue ? queue->size : 0;
}

void Queue_enqueue(Queue *queue, void *data) 
{
    if(!queue)return;
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    if (!node) return;

    node->data=data;
    node->next=NULL;
    if(queue->size==0)
    {
        queue->head=node;
        queue->tail=node;
    }else
    {
        queue->tail->next=node;
        queue->tail=node;
    }
    queue->size++;
}


//caller is responsible to free the memory allocated by the data returned by Queue_dequeue
void* Queue_dequeue(Queue *queue) 
{
    if (queue->size == 0) return NULL;
    QueueNode *node = queue->head; 
    void *data = node->data;
    queue->head = node->next;
    if (queue->size == 1) queue->tail = NULL;
    free(node);
    queue->size--;
    return data;
}

void* Queue_peek(Queue *queue) 
{
    if (queue->size == 0) return NULL;
    return queue->head->data;
}



void Queue_destroy(Queue *queue)
{
	 if (!queue) return;
    QueueNode *curr = queue->head;
    while (curr) 
    {
        QueueNode *next = curr->next;
        if (queue->freeFn) queue->freeFn(curr->data);
        free(curr);
        curr = next;
    }

    free(queue);
}
int Queue_isEmpty(Queue *queue)
{
    if(!queue)return 1;
    if(queue->size>0)return 0;
    return 1;
}

//Ietrator mehthods
static QueueIterator * Queue_getIterator(Queue *queue)
{
    return QueueIterator_new(queue->head);
}


//In C, static for functions means file-local visibility (not class-level, since C doesn't have classes
static int QueueIterator_hasNext(QueueIterator *iterator) 
{
    return iterator->current != NULL;
}

static void * QueueIterator_next(QueueIterator *iterator) 
{
    if (!iterator->current) return NULL;
    void *data = iterator->current->data;
    iterator->current = iterator->current->next;
    return data;
}

static void QueueIterator_destroy(QueueIterator *iterator) 
{
    free(iterator);
}

QueueIterator *QueueIterator_new(QueueNode *start) 
{
    QueueIterator *iterator = malloc(sizeof(QueueIterator));
    if (!iterator) return NULL;
    iterator->current = start;
    iterator->hasNext = QueueIterator_hasNext;
    iterator->next = QueueIterator_next;
    iterator->destroy = QueueIterator_destroy;
    return iterator;
}
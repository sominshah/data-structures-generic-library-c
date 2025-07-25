#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> // for size_t
#ifdef __cplusplus
extern "C" {          //"These functions have C-style names, do not mangle them."
#endif

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Queue development
 */

typedef void (*FreeFunctionQueue)(void *);
typedef struct QueueNode {
    void *data;
    struct QueueNode *next;
} QueueNode;

typedef struct QueueIterator
{
    QueueNode *current;
    int (*hasNext)(struct QueueIterator *);
    void *(*next)(struct QueueIterator *);
    void (*destroy)(struct QueueIterator *);
} QueueIterator;
 
QueueIterator *QueueIterator_new(QueueNode *start);



typedef struct Queue 
{
QueueNode *head;
QueueNode *tail;
size_t size;
FreeFunctionQueue freeFn;        
void (*enqueue)(struct Queue *queue,void * data);
void * (*dequeue)(struct Queue *queue);
void * (*peek)(struct Queue *queue);
size_t (*getSize)(struct Queue *queue);
int (*isEmpty)(struct Queue *queue);
void (*destroy)(struct Queue *queue);
QueueIterator *(*getIterator)(struct Queue *);

} Queue;

void Queue_freeData(void *data);
Queue * Queue_createQueue();                     
Queue* Queue_new(FreeFunctionQueue freeFn);

void Queue_enqueue(Queue *queue, void *data);
void * Queue_dequeue(Queue *queue);
void * Queue_peek(Queue *queue);
size_t Queue_getSize(Queue *queue);
void Queue_destroy(Queue *queue);
int Queue_isEmpty(Queue *queue);

#ifdef __cplusplus
}
#endif





#endif
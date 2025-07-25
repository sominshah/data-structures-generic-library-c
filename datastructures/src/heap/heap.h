#ifndef HEAP_H
#define HEAP_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {        
#endif

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-25
 * Description  : Heap development
 */

typedef void (*FreeFunctionHeap)(void *);
typedef int (*ComparatorFunctionHeap)(void *,void *);


typedef struct Heap 
{
void ** root;
size_t size;
size_t capacity;
FreeFunctionHeap freeFn;
ComparatorFunctionHeap comparator;


void (*add)(struct Heap *heap,void * data);
void * (*remove)(struct Heap *heap);
void * (*peek)(struct Heap *heap);
size_t (*getSize)(struct Heap *heap);
int (*isEmpty)(struct Heap *heap);
void (*destroy)(struct Heap *heap);
} Heap;

void Heap_freeData(void *data);

Heap * Heap_createHeap(ComparatorFunctionHeap comparator);
Heap* Heap_new(FreeFunctionHeap freeFn,ComparatorFunctionHeap comparator);


void Heap_add(Heap *heap, void *data);
void * Heap_remove(Heap *heap);
void * Heap_peek(Heap *heap);
size_t Heap_getSize(Heap *heap);
void Heap_destroy(Heap *heap);
int Heap_isEmpty(Heap *heap);

#ifdef __cplusplus
}
#endif


#endif
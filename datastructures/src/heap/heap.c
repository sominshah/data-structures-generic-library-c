/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-25
 * Description  : Generic heap implementation
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define INITIAL_CAPACITY 10

typedef void (*FreeFunctionHeap)(void *);
typedef int (*ComparatorFunctionHeap)(void *,void *);

static void heapifyUp(Heap *heap, int index); 

void Heap_freeData(void *data);
Heap * Heap_createHeap(ComparatorFunctionHeap comparator);                     
Heap* Heap_new(FreeFunctionHeap freeFn,ComparatorFunctionHeap comparator);
void Heap_add(Heap *heap, void *data);
void * Heap_remove(Heap *heap);
void * Heap_peek(Heap *heap);
size_t Heap_getSize(Heap *heap);
void Heap_destroy(Heap *heap);
int Heap_isEmpty(Heap *heap);


void Heap_freeData(void * data){free(data);}
Heap * Heap_createHeap(ComparatorFunctionHeap comparator){return Heap_new(Heap_freeData,comparator);}
Heap* Heap_new(FreeFunctionHeap freeFn,ComparatorFunctionHeap comparator)
{
Heap * heap = (Heap *) malloc(sizeof(Heap));
    if (!heap) return NULL;    

heap->capacity=INITIAL_CAPACITY;
heap->size=0;
heap->root=(void **)malloc(sizeof(void *) * heap->capacity);;
heap->freeFn=freeFn;
heap->comparator=comparator;


heap->add=Heap_add;
heap->remove=Heap_remove;
heap->peek=Heap_peek;
heap->getSize=Heap_getSize;
heap->isEmpty=Heap_isEmpty;
heap->destroy=Heap_destroy;
return heap;
}

static void swap(void **a, void **b) 
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}

size_t Heap_getSize(Heap *heap) {
    if (!heap) return 0;
    return heap->size;
}
int Heap_isEmpty(Heap *heap)
{
        return (!heap || heap->size==0)? 1:0;
}
void Heap_destroy(Heap *heap)
{
    if (!heap) return;
    for (size_t i = 0; i < heap->size; i++) {
        if (heap->freeFn) heap->freeFn(heap->root[i]);
    }
    free(heap->root);
    free(heap);
}


static void heapifyUp(Heap *heap, int index) 
{

    int parent = (index - 1) / 2;
    while (index > 0 && heap->comparator(heap->root[index], heap->root[parent]) < 0) 
    {
        swap(&heap->root[index], &heap->root[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

static void heapifyDown(Heap *heap, int index) 
{
    int left, right, smallest;
    while (1) 
    {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap->size && heap->comparator(heap->root[left], heap->root[smallest]) < 0)
            smallest = left;

        if (right < heap->size && heap->comparator(heap->root[right], heap->root[smallest]) < 0)
            smallest = right;

        if (smallest != index) {
            swap(&heap->root[index], &heap->root[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void Heap_add(Heap *heap, void *data) 
{
    if (heap->size == heap->capacity) 
    {
        heap->capacity *= 2;
        heap->root = (void **)realloc(heap->root, sizeof(void *) * heap->capacity);
    }
    heap->root[heap->size] = data;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void *Heap_remove(Heap *heap) {
    if (heap->size == 0) return NULL;

    void *min = heap->root[0];
    heap->size--;
    heap->root[0] = heap->root[heap->size];
    heapifyDown(heap, 0);
    return min;
}

void *Heap_peek(Heap *heap) {
    if (!heap || heap->size == 0) return NULL;
    return heap->root[0];
}

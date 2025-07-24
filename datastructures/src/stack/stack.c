/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Stack
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef void (*FreeFunctionStack)(void *);

Stack * Stack_clone(struct Stack *stack,FreeFunctionStack freeFn);
void Stack_push(Stack *stack, void *data);
void * Stack_pop(Stack *stack);
void * Stack_peek(Stack *stack);
size_t Stack_getSize(Stack *stack);
void Stack_destroy(Stack *stack);
int Stack_isEmpty(Stack *stack);
static StackIterator * Stack_getIterator(struct Stack *);


static int StackIterator_hasNext(StackIterator *iterator); 
static void *StackIterator_next(StackIterator *iterator); 
static void StackIterator_destroy(StackIterator *iterator); 
StackIterator *StackIterator_new(StackNode *start);



void Stack_freeInt(void *data);
void Stack_freeChar(void *data);
void Stack_freeFloat(void *data);
void Stack_freeDouble(void *data);
void Stack_freeString(void *data);


void Stack_freeInt(void *data)   { free(data); }
void Stack_freeChar(void *data)  { free(data); }
void Stack_freeFloat(void *data) { free(data); }
void Stack_freeDouble(void *data){ free(data); }
void Stack_freeString(void *data){ free(data); }


Stack * Stack_createIntStack();                     
Stack * Stack_createCharStack();
Stack * Stack_createFloatStack();                     
Stack * Stack_createDoubleStack();                    
Stack * Stack_createStringStack();                    
Stack* Stack_new(FreeFunctionStack freeFn);

Stack* Stack_createIntStack()    { return Stack_new(Stack_freeInt); }

Stack* Stack_createCharStack()   { return Stack_new(Stack_freeChar); }

Stack* Stack_createFloatStack()  { return Stack_new(Stack_freeFloat); }

Stack* Stack_createDoubleStack() { return Stack_new(Stack_freeDouble); }

Stack* Stack_createStringStack() { return Stack_new(Stack_freeString); }

Stack* Stack_new(FreeFunctionStack freeFn)
{
Stack * stack=(Stack *) malloc(sizeof(Stack));
if(stack==NULL)return NULL;    
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;

    stack->freeFn = freeFn;

    // Bind methods
    stack->clone = Stack_clone;
    stack->push = Stack_push;
    stack->pop = Stack_pop;
    stack->peek = Stack_peek;
    stack->getSize = Stack_getSize;
    stack->destroy = Stack_destroy;
    stack->isEmpty=Stack_isEmpty;
    stack->getIterator=Stack_getIterator;

    return stack;
}


size_t Stack_getSize(Stack *stack)
{
	  return stack ? stack->size : 0;
}


Stack* Stack_clone(Stack *stack, FreeFunctionStack freeFn) 
{
    if (!stack) return NULL;
    Stack *newStack = Stack_new(freeFn);
    if (!newStack) return NULL;

    StackNode *current = stack->head;
    StackNode **insertPtr = &(newStack->head);
    while (current) 
    {
        StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
        if (!newNode) 
        {
            newStack->destroy(newStack);
            return NULL;
        }
        newNode->data = current->data; // shallow copy
        newNode->next = NULL;
        *insertPtr = newNode;
        insertPtr = &(newNode->next);

        current = current->next;
        newStack->size++;
    }
    newStack->tail = newStack->head;
    while (newStack->tail && newStack->tail->next)
        newStack->tail = newStack->tail->next;
    return newStack;
}

void Stack_push(Stack *stack, void *data) 
{
    if(!stack)return;
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    if (!node) return;
    node->data = data;
    node->next = stack->head;
    stack->head = node;
    if (stack->size == 0) stack->tail = node;
    stack->size++;
}


//caller is responsible to free the memory allocated by the data returned by Stack_pop
void* Stack_pop(Stack *stack) 
{
    if(!stack)return NULL;
    if (stack->size == 0) return NULL;
    StackNode *top = stack->head;
    void *data = top->data;
    stack->head = top->next;
    if (stack->size == 1) stack->tail = NULL;
    free(top);
    stack->size--;
    return data;
}

void* Stack_peek(Stack *stack) 
{
    if(!stack)return NULL;
    if (stack->size == 0) return NULL;
    return stack->head->data;
}



void Stack_destroy(Stack *stack)
{

	 if (!stack) return;
    StackNode *curr = stack->head;
    while (curr) 
    {
        StackNode *next = curr->next;
        if (stack->freeFn) stack->freeFn(curr->data);
        free(curr);
        curr = next;
    }

    free(stack);
}
int Stack_isEmpty(Stack *stack)
{

    if(!stack)return 1;
    if(stack->size>0)return 0;
    return 1;
}


//Ietrator methods
static StackIterator * Stack_getIterator(Stack *stack)
{
    return StackIterator_new(stack->head);
}

static int StackIterator_hasNext(StackIterator *iterator) 
{
    return iterator->current != NULL;
}

static void * StackIterator_next(StackIterator *iterator) 
{
    if (!iterator->current) return NULL;
    void *data = iterator->current->data;
    iterator->current = iterator->current->next;
    return data;
}

static void StackIterator_destroy(StackIterator *iterator) 
{
    free(iterator);
}

StackIterator *StackIterator_new(StackNode *start) 
{
    StackIterator *iterator = malloc(sizeof(StackIterator));
    if (!iterator) return NULL;
    iterator->current = start;
    iterator->hasNext = StackIterator_hasNext;
    iterator->next = StackIterator_next;
    iterator->destroy = StackIterator_destroy;
    return iterator;
}
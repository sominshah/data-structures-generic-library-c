#ifndef STACK_H
#define STACK_H

#include <stddef.h> // for size_t
#ifdef __cplusplus
extern "C" {          //"These functions have C-style names, do not mangle them."
#endif

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-24
 * Description  : Stack development
 */

typedef void (*FreeFunctionStack)(void *);
typedef struct StackNode {
    void *data;
    struct StackNode *next;
} StackNode;


typedef struct StackIterator
{
    StackNode *current;
    int (*hasNext)(struct StackIterator *);
    void *(*next)(struct StackIterator *);
    void (*destroy)(struct StackIterator *);
} StackIterator;
 
StackIterator *StackIterator_new(StackNode *start);


typedef struct Stack 
{
StackNode *head;
StackNode *tail;
size_t size;
FreeFunctionStack freeFn;        
struct Stack * (*clone)(struct Stack *stack,FreeFunctionStack freeFn);
void (*push)(struct Stack *stack,void * data);
void * (*pop)(struct Stack *stack);
void * (*peek)(struct Stack *stack);
size_t (*getSize)(struct Stack *stack);
int (*isEmpty)(struct Stack *stack);
void (*destroy)(struct Stack *stack);
StackIterator *(*getIterator)(struct Stack *);
} Stack;

void Stack_freeInt(void *data);
void Stack_freeChar(void *data);
void Stack_freeFloat(void *data);
void Stack_freeDouble(void *data);
void Stack_freeString(void *data);

Stack * Stack_createIntStack();                     
Stack * Stack_createCharStack();
Stack * Stack_createFloatStack();                     
Stack * Stack_createDoubleStack();                    
Stack * Stack_createStringStack();                    
Stack* Stack_new(FreeFunctionStack freeFn);


Stack * Stack_clone(struct Stack *stack,FreeFunctionStack freeFn);
void Stack_push(Stack *stack, void *data);
void * Stack_pop(Stack *stack);
void * Stack_peek(Stack *stack);
size_t Stack_getSize(Stack *stack);
void Stack_destroy(Stack *stack);
int Stack_isEmpty(Stack *stack);

#ifdef __cplusplus
}
#endif





#endif
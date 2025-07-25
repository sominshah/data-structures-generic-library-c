#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    Stack *stack = Stack_createStack(); // Your wrapper
    for (int i = 0; i < 5; i++) 
    {
        int *val = malloc(sizeof(int));
        *val = i;
        stack->push(stack, val);
    }

    printf("Stack Size:%d \n",stack->getSize(stack));


    printf("Printing stack elements by iterator\n");

    StackIterator * itr = stack->getIterator(stack);
    int i=0;
    while(itr->hasNext(itr))
    {
        int * val = itr->next(itr);
        printf("\nElement At the poisition %d: %d\n",i,*val);
        i++;
    }

    while(!stack->isEmpty(stack))
    {
        int *val = stack->pop(stack);
        printf("Removig Element : %d\n", *val);
        free(val);
    }

    printf("Stack Size After POP Operation:%d \n",stack->getSize(stack));

    stack->destroy(stack);
    return 0;
}

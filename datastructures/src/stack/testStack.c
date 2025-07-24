#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    Stack *stack = Stack_createIntStack(); // Your wrapper
    for (int i = 0; i < 5; i++) 
    {
        int *val = malloc(sizeof(int));
        *val = i;
        stack->push(stack, val);
    }

    printf("Stack Size:%d \n",stack->getSize(stack));

    while(!stack->isEmpty(stack))
    {
        int *val = stack->pop(stack);
        printf("Element : %d\n", *val);
        free(val);
    }

    stack->destroy(stack);
    return 0;
}

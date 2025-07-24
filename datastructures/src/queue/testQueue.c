#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    Queue *queue = Queue_createIntQueue(); // Your wrapper
    for (int i = 0; i < 5; i++) 
    {
        int *val = malloc(sizeof(int));
        *val = i;
        queue->enqueue(queue, val);
    }

    printf("\nQueue Size:%d \n",queue->getSize(queue));


    printf("Prinint queue elements by iterator\n");

    QueueIterator * itr = queue->getIterator(queue);
    int i=0;
    while(itr->hasNext(itr))
    {
        int * val = itr->next(itr);
        printf("\nElement At the poisition %d: %d\n",i,*val);
        i++;
    }

    while(!queue->isEmpty(queue))
    {
        int *val = queue->dequeue(queue);
        printf(" Removing Element : %d\n", *val);
        free(val);
    }


    printf("Queue Size After Dequeue Operation:%d \n",queue->getSize(queue));

    queue->destroy(queue);
    return 0;
}

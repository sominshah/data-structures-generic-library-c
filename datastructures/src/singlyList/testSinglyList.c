#include "singlyList.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() {
    SinglyList *list = SinglyList_createList(); // Your wrapper
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list->listAdd(list, val);
    }

    for (size_t i = 0; i < list->listSize(list); i++) {
        int *val = list->listGet(list, i);
        printf("Element %zu: %d\n", i, *val);
    }

    //List Iterating via Iterator-
    printf("Printing via iterator\n");

    SinglyListIterator *iterator = list->getIterator(list);   

    //or you can add iterator like below directly -
    //SinglyListIterator * iterator= SinglyListIterator_new(list->head); 


        while (iterator->hasNext(iterator)) 
        {
            int * value = (int *) iterator->next(iterator);
            printf("%d\n", *value);
        }
        iterator->destroy(iterator);
    list->destroyList(list);
    return 0;
}

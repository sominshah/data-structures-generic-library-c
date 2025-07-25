#include "doublyList.h"
#include <stdio.h>
#include <stdlib.h>

void freeInt(void *data) {
    free(data);
}

int main() 
{
    DoublyList *list = DoublyList_createList(); // Your wrapper
    for (int i = 0; i < 5; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        list->insertAt(list,i, val);
    }

    for (size_t i = 0; i < list->listSize(list); i++) {
        int *val = list->listGet(list, i);
        printf("Element %zu: %d\n", i, *val);
    }

    //List Iterating via Iterator-
    printf("Printing via iterator\n");

    DoublyListIterator *iterator = list->getIterator(list);   

    //or you can add iterator like below directly -
    //DoublyListIterator * iterator= DoublyListIterator_new(list->head); 


        while (iterator->hasNext(iterator)) 
        {
            int * value = (int *) iterator->next(iterator);
            printf("%d\n", *value);
        }
        iterator->destroy(iterator);


    printf("Printing via reverse iterator\n");

    DoublyListIterator *itr = list->getReverseIterator(list);   

    //or you can add iterator like below directly -
    //DoublyListIterator * iterator= DoublyListIterator_new(list->head); 
        while (itr->hasPrevious(itr)) 
        {
            int * value = (int *) itr->previous(itr);
            printf("%d\n", *value);
        }
        itr->destroy(itr); 

    list->destroyList(list);
    return 0;
}

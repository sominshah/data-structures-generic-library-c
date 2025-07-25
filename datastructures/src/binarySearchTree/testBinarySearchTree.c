#include "binarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>

int intComparator(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

void printInt(void *data) {
    printf("%d ", *(int *)data);
}

int main() {
    BinarySearchTree *tree = bst_createBST(intComparator);

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) {
        int *val = malloc(sizeof(int));
        *val = values[i];
        tree->add(tree, val);
    }

    printf("InOrder: ");
    tree->inOrder(tree, printInt);
    printf("\n");

    int key = 30;
    int *found = tree->find(tree, &key);
    printf("Find %d: %s\n", key, found ? "Found" : "Not Found");

    tree->destroy(tree);
    return 0;
}

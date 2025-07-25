#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stddef.h> 

#ifdef __cplusplus
extern "C" {      
#endif

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-25
 * Description  : BinarySearchTree development
 */

typedef void (*FreeFunctionBST)(void *);
typedef int  (*ComparatorFunctionBST)(void *, void *); // must return <0, 0, >0 like strcmp

typedef struct BinarySearchTreeNode {
    void *data;
    struct BinarySearchTreeNode *left;
    struct BinarySearchTreeNode *right;
} BinarySearchTreeNode;

typedef struct BinarySearchTree {
    BinarySearchTreeNode *root;
    size_t size;

    FreeFunctionBST freeFn;
    ComparatorFunctionBST comparator;

    // Member functions
    void (*add)(struct BinarySearchTree *tree, void *data);
    void *(*remove)(struct BinarySearchTree *tree, void *key);
    void *(*find)(struct BinarySearchTree *tree, void *key);
    int (*isEmpty)(struct BinarySearchTree *tree);
    size_t (*getSize)(struct BinarySearchTree *tree);    
    void (*destroy)(struct BinarySearchTree *tree);
    void (*clear)(struct BinarySearchTree *tree);


    void (*inOrder)(struct BinarySearchTree *, void (*visit)(void *));
    void (*preOrder)(struct BinarySearchTree *, void (*visit)(void *));
    void (*postOrder)(struct BinarySearchTree *, void (*visit)(void *));
    void (*levelOrder)(struct BinarySearchTree *, void (*visit)(void *));
    
    size_t (*getHeight)(struct BinarySearchTree *tree); 


} BinarySearchTree;

// Internal helpers (optional for user)
void bst_freeData(void *data);

// Constructors
BinarySearchTree *bst_createBST(ComparatorFunctionBST comparator);
BinarySearchTree *bst_new(FreeFunctionBST freeFn, ComparatorFunctionBST comparator);

// Operations (if user calls directly instead of through tree->add etc.)
void bst_add(BinarySearchTree *tree, void *data);
void *bst_remove(BinarySearchTree *tree, void *key); // Optional for v1
void *bst_find(BinarySearchTree *tree, void *key);
int bst_isEmpty(BinarySearchTree *tree);
size_t bst_getSize(BinarySearchTree *tree);
void bst_destroy(BinarySearchTree *tree);
void bst_clear(BinarySearchTree *tree);


    //visit function is user-defined function, It's user's choice what he/she wants to do with data while traversing
    void bst_inOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_preOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_postOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_levelOrder(struct BinarySearchTree *, void (*visit)(void *));

    size_t bst_getHeight(BinarySearchTree *tree); 

#ifdef __cplusplus
}
#endif

#endif

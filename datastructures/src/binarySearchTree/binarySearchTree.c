#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-25
 * Description  : BinarySearchTree development
 */

typedef void (*FreeFunctionBST)(void *);
typedef int  (*ComparatorFunctionBST)(void *, void *); // must return <0, 0, >0 like strcmp

// Internal helpers (optional for user)
void bst_freeData(void *data);

// Constructors
BinarySearchTree *bst_createBST(ComparatorFunctionBST comparator);
BinarySearchTree *bst_new(FreeFunctionBST freeFn, ComparatorFunctionBST comparator);


void bst_add(BinarySearchTree *tree, void *data);
void *bst_remove(BinarySearchTree *tree, void *key);
void *bst_find(BinarySearchTree *tree, void *key);
int bst_isEmpty(BinarySearchTree *tree);
void bst_destroy(BinarySearchTree *tree);
void bst_clear(BinarySearchTree *tree);
size_t bst_getSize(BinarySearchTree *tree);

//traversal functions
    void bst_inOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_preOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_postOrder(struct BinarySearchTree *, void (*visit)(void *));
    void bst_levelOrder(struct BinarySearchTree *, void (*visit)(void *));




static size_t bst_nodeHeight(BinarySearchTreeNode *node);
size_t bst_getHeight(BinarySearchTree *tree);


void bst_freeData(void * data){free(data);}

BinarySearchTree *bst_createBST(ComparatorFunctionBST comparator)
{
    return bst_new(bst_freeData,comparator);
}

BinarySearchTree *bst_new(FreeFunctionBST freeFn, ComparatorFunctionBST comparator)
{
    BinarySearchTree *tree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    tree->root = NULL;
    tree->size = 0;
    tree->freeFn = freeFn;
    tree->comparator = comparator;

    tree->add = bst_add;
    tree->remove = bst_remove;
    tree->find = bst_find;
    tree->isEmpty = bst_isEmpty;
    tree->destroy = bst_destroy;
    tree->clear=bst_clear;
    tree->inOrder=bst_inOrder;
    tree->preOrder=bst_preOrder;
    tree->postOrder=bst_postOrder;
    tree->levelOrder=bst_levelOrder;

    return tree;
}

BinarySearchTreeNode* createNode(void *data)
{
    BinarySearchTreeNode *node = (BinarySearchTreeNode *)malloc(sizeof(BinarySearchTreeNode));
    if (!node) return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void bst_add(BinarySearchTree *tree, void *data)
{
    if (!tree) return;

    BinarySearchTreeNode *newNode = createNode(data);
    if (tree->root == NULL)
    {
        tree->root = newNode;
        tree->size++;
        return;
    }
    BinarySearchTreeNode *current = tree->root;
    BinarySearchTreeNode *parent = NULL;

    while (current != NULL)
    {
        parent = current;
        int cmp = tree->comparator(data, current->data);
        if (cmp < 0)
        {
            current = current->left;
        }
        else if (cmp > 0)
        {
            current = current->right;
        }
        else
        {
            // Duplicate key, replace or ignore. Here we ignore.
            tree->freeFn(newNode->data);
            free(newNode);
            return;
        }
    }

    // Attach newNode to correct parent side
    if (tree->comparator(data, parent->data) < 0)
        parent->left = newNode;
    else
        parent->right = newNode;

    tree->size++;
}

int bst_isEmpty(BinarySearchTree *tree)
{
    return (tree == NULL || tree->size == 0);
}
size_t bst_getSize(BinarySearchTree *tree)
{
    if (!tree)return 0;
    return tree->size;
}

void * bst_remove(BinarySearchTree *tree, void *key)
{
    if (!tree || !key || !tree->root) return NULL;

    BinarySearchTreeNode *parent = NULL;
    BinarySearchTreeNode *current = tree->root;
    int cmp = 0;

    // Find the node to remove
    while (current && (cmp = tree->comparator(key, current->data)) != 0)
    {
        parent = current;
        if (cmp < 0)
            current = current->left;
        else
            current = current->right;
    }

    if (!current) return NULL; // Key not found

    void *removedData = current->data;

    // Helper to replace parent's child pointer
    void replaceChild(BinarySearchTreeNode *parent, BinarySearchTreeNode *oldChild, BinarySearchTreeNode *newChild)
    {
        if (!parent)
            tree->root = newChild;
        else if (parent->left == oldChild)
            parent->left = newChild;
        else if (parent->right == oldChild)
            parent->right = newChild;
    }

    // Case 1: Node has no child
    if (!current->left && !current->right)
    {
        replaceChild(parent, current, NULL);
        free(current);
    }
    // Case 2: Node has one child
    else if (!current->left || !current->right)
    {
        BinarySearchTreeNode *child = current->left ? current->left : current->right;
        replaceChild(parent, current, child);
        free(current);
    }
    // Case 3: Node has two children
    else
    {
        // Find in-order successor (leftmost in right subtree)
        BinarySearchTreeNode *successorParent = current;
        BinarySearchTreeNode *successor = current->right;
        while (successor->left)
        {
            successorParent = successor;
            successor = successor->left;
        }

        // Swap data pointers
        void *tempData = current->data;
        current->data = successor->data;
        successor->data = tempData;

        // Recursively delete successor
        // successor has at most one child (right)
        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;

        free(successor);
    }

    tree->size--;
    return removedData;
}



void *bst_find(BinarySearchTree *tree, void *key)
{
    if (!tree || !key) return NULL;

    BinarySearchTreeNode *current = tree->root;
    int cmp;

    while (current)
    {
        cmp = tree->comparator(key, current->data);

        if (cmp == 0)
        {
            return current->data;  // Found
        }
        else if (cmp < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return NULL; // Not found
}

static void bst_freeNode(BinarySearchTreeNode *node, FreeFunctionBST freeFn)
{
    if (!node) return;
    bst_freeNode(node->left, freeFn);
    bst_freeNode(node->right, freeFn);
    if (freeFn) freeFn(node->data);
    free(node);
}

void bst_destroy(BinarySearchTree *tree)
{
    if (!tree) return;
    bst_freeNode(tree->root, tree->freeFn);
    free(tree);
}

void bst_clear(BinarySearchTree *tree)
{
    if (!tree) return;

    bst_freeNode(tree->root, tree->freeFn);
    tree->root = NULL;
    tree->size = 0;
}

    static void inOrderTraversal(BinarySearchTreeNode *node, void (*visit)(void *)) 
    {
    if (!node) return;
    inOrderTraversal(node->left, visit);
    visit(node->data);
    inOrderTraversal(node->right, visit);
    }

void bst_inOrder(struct BinarySearchTree *tree, void (*visit)(void *)) 
{
    if (!tree || !visit) return;
    inOrderTraversal(tree->root, visit);
}

 static void preOrderTraversal(BinarySearchTreeNode *node, void (*visit)(void *)) {
    if (!node) return;
    visit(node->data);
    preOrderTraversal(node->left, visit);
    preOrderTraversal(node->right, visit);
}

void bst_preOrder(struct BinarySearchTree *tree, void (*visit)(void *)) {
    if (!tree || !visit) return;
    preOrderTraversal(tree->root, visit);
}



static void postOrderTraversal(BinarySearchTreeNode *node, void (*visit)(void *)) {
    if (!node) return;
    postOrderTraversal(node->left, visit);
    postOrderTraversal(node->right, visit);
    visit(node->data);
}

void bst_postOrder(struct BinarySearchTree *tree, void (*visit)(void *)) {
    if (!tree || !visit) return;
    postOrderTraversal(tree->root, visit);
}




typedef struct TreeNodeQueue {
    BinarySearchTreeNode *bstNode;
    struct TreeNodeQueue *next;
} TreeNodeQueue;

typedef struct {
    TreeNodeQueue *front;
    TreeNodeQueue *rear;
} Queue;

static Queue *createQueue() {
    Queue *q = malloc(sizeof(Queue));
    if(!q)return NULL;
    q->front = q->rear = NULL;
    return q;
}

static void enqueue(Queue *q, BinarySearchTreeNode *node) {
    TreeNodeQueue *newNode = malloc(sizeof(TreeNodeQueue));
    newNode->bstNode = node;
    newNode->next = NULL;
    if (!q->rear) q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

static BinarySearchTreeNode *dequeue(Queue *q) {
    if (!q->front) return NULL;
    TreeNodeQueue *temp = q->front;
    BinarySearchTreeNode *node = temp->bstNode;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return node;
}

static int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

static void destroyQueue(Queue *q) 
{
    while (!isQueueEmpty(q)) dequeue(q);
    free(q);
}

void bst_levelOrder(struct BinarySearchTree *tree, void (*visit)(void *)) {
    if (!tree || !tree->root || !visit) return;

    Queue *q = createQueue();
    if(!q)return;

    enqueue(q, tree->root);

    while (!isQueueEmpty(q)) {
        BinarySearchTreeNode *current = dequeue(q);
        visit(current->data);
        if (current->left) enqueue(q, current->left);
        if (current->right) enqueue(q, current->right);
    }

    destroyQueue(q);
}


static size_t bst_nodeHeight(BinarySearchTreeNode *node) {
    if (!node) return -1;
    int leftHeight = bst_nodeHeight(node->left);
    int rightHeight = bst_nodeHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

size_t bst_getHeight(BinarySearchTree *tree) {
    if (!tree) return -1;
    return bst_nodeHeight(tree->root);
}

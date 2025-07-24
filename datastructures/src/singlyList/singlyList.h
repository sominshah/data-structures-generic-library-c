#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stddef.h> // for size_t

/*
* C++ uses name mangling, which changes function names internally to support overloading. C does not do this.
* When a C++ program tries to link with a C function (from a .c file), 
* it might not find the correct symbol name, unless we tell the C++ compiler to treat those functions with C linkage
*/
#ifdef __cplusplus
extern "C" {          //"These functions have C-style names, do not mangle them."
#endif

#define AUTHOR_SIGNATURE "Author: Somin Ali | 2025"
#define AUTHOR_EMAIL "Email: ssssomin4@gmail.com"
#define AUTHOR_GITHUB "GitHub Link: https://sominshah.github.io/index.html"

/*
 * Author       : Somin Ali
 * Email        : ssssomin4@gmail.com
 * GitHub       : https://sominshah.github.io/index.html
 * Created on   : 2025-07-23
 * Description  : Singly Linked List
 */

typedef void (*FreeFunction)(void *);
typedef struct SinglyListNode {
    void *data;
    struct SinglyListNode *next;
} SinglyListNode;


typedef struct SinglyListIterator {
    SinglyListNode *current;

    int (*hasNext)(struct SinglyListIterator *iterator);
    void *(*next)(struct SinglyListIterator *iterator);
    void (*destroy)(struct SinglyListIterator *iterator);

} SinglyListIterator;


typedef struct SinglyList 
{
SinglyListNode *head;
SinglyListNode *tail;
size_t size;
FreeFunction freeFn;        
struct SinglyList * (*cloneList)(struct SinglyList *list,FreeFunction freeFn);
void (*listAdd)(struct SinglyList *list, void *data);
void * (*listGet)(struct SinglyList *list, size_t index);
void (*listRemoveAt)(struct SinglyList *list, size_t index);
size_t (*listSize)(struct SinglyList *list);
void (*destroyList)(struct SinglyList *list);
SinglyListIterator *(*getIterator)(struct SinglyList *);
} SinglyList;





SinglyListIterator *SinglyListIterator_new(SinglyListNode *start); 




void SinglyList_freeInt(void *data);
void SinglyList_freeChar(void *data);
void SinglyList_freeFloat(void *data);
void SinglyList_freeDouble(void *data);
void SinglyList_freeString(void *data);

SinglyList * SinglyList_createIntList();                     
SinglyList * SinglyList_createCharList();
SinglyList * SinglyList_createFloatList();                     
SinglyList * SinglyList_createDoubleList();                    
SinglyList * SinglyList_createStringList();                    
SinglyList* SinglyList_new(FreeFunction freeFn);


SinglyList * SinglyList_cloneList(struct SinglyList *list,FreeFunction freeFn);
void SinglyList_listAdd(SinglyList *list, void *data);
void * SinglyList_listGet(SinglyList *list, size_t index);
void SinglyList_listRemoveAt(SinglyList *list, size_t index);
size_t SinglyList_listSize(SinglyList *list);
void SinglyList_destroyList(SinglyList *list);
#ifdef __cplusplus
}
#endif







#endif
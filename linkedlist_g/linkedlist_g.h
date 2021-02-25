#ifndef LINKEDLIST_G
#define LINKEDLIST_G
#include <stdbool.h>

typedef struct _List *List;
typedef void (*freeFunction)(void *);

void list_new(List *list, int elementSize, freeFunction freeFn);
void list_destroy(List *list);
void list_prepend(List *list, void *element); //adds a node to the head
void list_append(List *list, void *element);  //adds a node to the tail

void *listGetFirst(List *list);
void *listGetNext(List *list);
bool listIsEmpty(List *list);

#define LLIST_FOREACH(Type, element, list)   \
    for (Type element = listGetFirst(list); listIsEmpty(list) == false; element = listGetNext(list))

#endif
#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>


typedef struct _listNode link_Node;
typedef struct list list;
typedef void (*freeFunction)(void *);

void list_new(list *list, int elementSize, freeFunction freeFn);
void list_destroy(list *list);
void list_prepend(list *list, void *element);//adds a node to the head
void list_append(list *list, void *element); //adds a node to the tail

list * get_First(list *list);
list * get_Next(list *list);
list * Is_Done(list *list);

// to ask tal !!!! 
// you must ask tal !!!!!
#define List_FOREACH(Type, element, data) \
for (Type element = ListGetFirst(data) ; \
data != NULL; element=ListGetNext(data))

#endif


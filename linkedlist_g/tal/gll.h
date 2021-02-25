#ifndef _GLL_H
#define _GLL_H
#include <stdbool.h>

typedef void *Element;
typedef void (*freeFunction)(Element);
typedef Element (*ElemCopyFunction)(Element);

typedef struct _list *List;
typedef struct _listNode *ListNode;

void list_new(List *list, int elementSize, freeFunction freeFn, ElemCopyFunction copyFn);
void list_destroy(List list);
 
void list_prepend(List , Element);
void list_append(List , Element);
int list_size(List );


#endif
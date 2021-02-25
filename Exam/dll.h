#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _Node* Node;
typedef struct _dlist* DList;
typedef enum {Fail, Success} Result ;

Result createList(DList *list);
Result preAppend(DList list,int x);
Result append(DList list,int x) ;
void Print(DList list) ;
void ReversePrint(DList list) ;
void destroyList(DList list);
#endif /* _DLIST_H_ */
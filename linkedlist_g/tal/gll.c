
#include <stdlib.h>
#include <assert.h>

#include "gll.h"

struct _listNode{
  Element data;
  struct _listNode *next;
};
 
struct _list{
  int logicalLength;
  int elementSize;
  ListNode head;
  ListNode tail;
  freeFunction freeFn;
  ElemCopyFunction copyFn;
};

void list_new(List *list, int elementSize, freeFunction freeFn, ElemCopyFunction copyFn){
    assert(elementSize>0);
    assert(freeFn!=NULL && copyFn!=NULL);

    *list=(List *)malloc(sizeof(struct _list));
    assert(list !=NULL);

    (*list)->copyFn=copyFn;
    (*list)->freeFn=freeFn;
    (*list)->elementSize=elementSize;
    (*list)->head=(*list)->tail=NULL;
    (*list)->logicalLength=0;
}

void list_destroy(List list){
    ListNode curr;
    while (list->head!=NULL){
        curr=list->head;
        list->head=curr->next;

        list->freeFn(curr->data);
        free(curr);
    }
    free(list);
}
 
void list_prepend(List list, Element element){
    ListNode newNode=(ListNode)malloc(sizeof(struct _listNode));
    assert(newNode!=NULL);

    newNode->data=list->copyFn(element);
    newNode->next=list->head;
    list->head=newNode;

    if(!list->tail){
        list->tail=list->head;
    }

    list->logicalLength++;
}

void list_append(List list, Element element){
    ListNode newNode=(ListNode)malloc(sizeof(struct _listNode));
    assert(newNode!=NULL);

    newNode->data=list->copyFn(element);
    newNode->next=NULL;

    if(list->logicalLength==0){
        list->head=list->tail=newNode;
    }
    else{
        list->tail->next=newNode;
        list->tail=newNode;
    }
    list->logicalLength++;
}

int list_size(List list){
    return list->logicalLength;
}
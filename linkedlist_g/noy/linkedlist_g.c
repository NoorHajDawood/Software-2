#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist_g.h"

typedef struct _listNode {
 void *data;
 struct _listNode *next;
} listNode;
typedef struct {
 int logicalLength; //number of nodes
 int elementSize;//sizeof each element
 listNode *head;
 listNode *tail;
 freeFunction freeFn; //func pointer to free every element
} list;


void list_new(list *list, int elementSize, freeFunction freeFn){

    list->elementSize = elementSize;
    list->freeFn = freeFn;
    list->head = NULL;
    list->tail = NULL;
    list->logicalLength = 0;
}

void list_destroy(list *list){

    for (int i = 0; i < list->logicalLength; i++)
    {
        listNode *temp = list->head->next;
        list->freeFn(list->head->data);
        list->freeFn(list->head);
        list->head = temp;
    }
}
void list_prepend(list *list, void *element){//adds a node to the head

    listNode *newNode = malloc (sizeof(listNode));
    if(newNode == NULL) return;

    newNode->data = element;
    newNode->next = list->head;

    list->head = newNode;

    if(list->tail == NULL)
        list->tail = list->head;// כאשר האיבר שהוספנו הוא הראשון, נרצה שהוא יהיה הזנב

    list->logicalLength++;

}

void list_append(list *list, void *element){

    listNode *newNode = malloc (sizeof(listNode));
    if(newNode == NULL) return;

    newNode->data = element;
    newNode->next = NULL;

    list->tail->next = newNode;
    list->tail = newNode;

    list->logicalLength++;
} //adds a node to the tail


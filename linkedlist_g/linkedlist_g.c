#include "linkedlist_g.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _listNode
{
    void *data;
    struct _listNode *next;
} listNode;
typedef struct _List
{
    int logicalLength; //number of nodes
    int elementSize;   //sizeof each element
    listNode *head;
    listNode *tail;
    freeFunction freeFn; //func pointer to free every element
    listNode *iterator; // iterator ^_^
};

void list_new(List *list, int elementSize, freeFunction freeFn)
{
    *list = malloc(sizeof(**list));
    (*list)->elementSize = elementSize;
    (*list)->freeFn = freeFn;
    (*list)->logicalLength = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->iterator = NULL;
}
void list_destroy(List *list)
{
    LLIST_FOREACH(listNode*, tmp, list)
    {
        (*list)->freeFn(tmp->data);
        free(tmp);
    }
    free(list);
}
void list_prepend(List *list, void *element) //adds a node to the head
{
    listNode* node = malloc(sizeof(*node));
    node->data = element;
    node->next = (*list)->head;
    (*list)->logicalLength++;
    if((*list)->head == NULL)
        (*list)->tail = node;
    (*list)->head = node;


}
void list_append(List *list, void *element)  //adds a node to the tail
{
    listNode* node = malloc(sizeof(*node));
    node->data = element;
    node->next = NULL;
    (*list)->logicalLength++;
    if((*list)->tail != NULL)
        (*list)->tail->next = node;
    (*list)->tail = node;
}

void *listGetFirst(List *list)
{
    return (*list)->iterator = (*list)->head;
}
void *listGetNext(List *list)
{
    return (*list)->iterator->next;
}
bool listIsEmpty(List *list)
{
    return (*list)->iterator == NULL;
}
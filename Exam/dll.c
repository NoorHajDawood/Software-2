#include "dll.h"

typedef struct _Node
{
    int data;
    Node prev, next;
};

typedef struct _dlist
{
    Node head, tail;
    int size;
};

static Result createNode(int x, Node *node)
{
    if(node == NULL)
        return Fail;
    *node = (Node)malloc(sizeof(struct _Node));
    if (*node = NULL)
        return Fail;
    (*node)->next = (*node)->prev = NULL;
    (*node)->data = x;
}

Result createList(DList *list)
{
    if(list == NULL)
        return Fail;
    *list = (DList)malloc(sizeof(struct _dlist));
    if (list == NULL)
        return Fail;
    (*list)->head = (*list)->tail = NULL;
    (*list)->size = 0;
    return Success;
}

Result preAppend(DList list, int x)
{
    Node node;
    if(createNode(x, &node) == Fail)
        return Fail;
    if (list->head)
    {
        node->next = list->head;
        list->head->prev = node;
    }
    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
    ++list->size;
    return Success;
}

Result append(DList list, int x)
{
    Node node;
    if(createNode(x, &node) == Fail)
        return Fail;
    if (list->tail)
    {
        node->prev = list->tail;
        list->tail->next = node;
    }
    list->tail = node;
    if (list->head == NULL)
        list->head = node;
    ++list->size;
    return Success;
}

void Print(DList list)
{
    if(list == NULL)
        return;
    for (Node i = list->head; i; i = i->next)
    {
        printf("%d -> ", i->data);
    }
    printf("NULL\n");
}
void ReversePrint(DList list)
{
    if(list == NULL)
        return;
    for (Node i = list->tail; i; i = i->prev)
    {
        printf("%d -> ", i->data);
    }
    printf("NULL\n");
}
void destroyList(DList list)
{
    if(list == NULL)
        return;
    for (Node i = list->head, next; i; i = next)
    {
        next = i->next;
        free(i);
    }
    free(list);
}
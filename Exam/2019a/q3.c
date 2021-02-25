#include <stdlib.h>
typedef struct node
{
    int key;
    struct node* next;
} Node;
Node *add_sorted(Node *head, int val){
    if(head == NULL){
        head = malloc(sizeof(Node));
        head->key = val;
        head->next = NULL;
        return head;
    }
    if(head->key > val){
        Node *new = malloc(sizeof(Node));
        new->key = val;
        new->next = head;
        return new;
    }
    Node *tmp = head;
    while(tmp->next != NULL && tmp->key < val)
        tmp = tmp->next;
    Node *new = malloc(sizeof(Node));
    new->key = val;
    new->next = tmp->next;
    tmp->next = new;
    return head;
}
Node *delete(Node *head, int val){
    if(head == NULL)
        return;
    Node *tmp;
    while (head != NULL && head->key == val)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    if(head == NULL)
        return;
    Node *prev = head;
    tmp = head->next;
    while(tmp != NULL){
        if(tmp->key == val)
        {
            prev->next = tmp->next;
            free(tmp);
            tmp = prev->next;
            continue;
        }
        prev=prev->next;
        tmp=tmp->next;
    }
}
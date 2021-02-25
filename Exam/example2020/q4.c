#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int num;
    struct node* next;
} Node;
Node* delete_min(Node* head)
{
    if(head == NULL)
        return NULL;
    int min = head->num;
    Node *tmp = head;
    while(tmp != NULL)
    {
        if(tmp->num < min)
        {
            min = tmp->num;
        }
        tmp = tmp->next;
    }
    tmp = head;
    if(tmp->num == min)
    {
        head = head->next;
        free(tmp);
        return head;
    }
    while(tmp->next->num != min)
    {
        tmp = tmp->next;
    }
    Node *del = tmp->next;
    tmp->next=tmp->next->next;
    free(del);
    return head;
}
void printNode(Node *head)
{
    while(head != NULL)
    {
        printf("%d->",head->num);
        head= head->next;
    }
    printf("NULL\n");
}
int main(int argc, char const *argv[])
{
    int x;
    Node* head = NULL;
    Node* tmp;
    do{
        scanf("%d",&x);
        if(x>=0)
        {
            if(head==NULL)
            {
                head = malloc(sizeof(Node));
                head->num=x;
                head->next=NULL;
                tmp = head;
            }
            else
            {
                tmp->next = malloc(sizeof(Node));
                tmp = tmp->next;
                tmp->num = x;
                tmp->next = NULL;
            }
        }
    }while(x>=0);
    printNode(head);
    head = delete_min(head);
    printNode(head);
    return 0;
}

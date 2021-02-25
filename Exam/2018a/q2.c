#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _date{
    int day;
    int month;
    int year;
} Date;
typedef struct _birthday{
    char *name;
    Date date;
    Birthday next;
} *Birthday;
int dateCompare(Date date1, Date date2){
    if(date1.year > date2.year)
        return 1;
    if(date1.year < date2.year)
        return -1;
    if(date1.month > date2.month)
        return 1;
    if(date1.month < date2.month)
        return -1;
    if(date1.day > date2.day)
        return 1;
    if(date1.day < date2.day)
        return -1;
    return 0;
}
Birthday* date_subset(Birthday* head, Date date){
    Birthday *new = NULL, tmp;
    while(*head != NULL){
        if(dateCompare((*head)->date, date) == 0){
            if(new == NULL){
                new = malloc(sizeof(Birthday));
                (*new)->date = (*head)->date;
                (*new)->name = malloc(strlen((*head)->name)+1);
                strcpy((*new)->name, (*head)->name);
                (*new)->next = NULL;
                tmp = *new;
            }
            else
            {
                tmp->next = malloc(sizeof(Birthday));
                tmp = tmp->next;
                tmp->date = (*head)->date;
                tmp->name = malloc(strlen((*head)->name)+1);
                strcpy(tmp->name, (*head)->name);
                tmp->next = NULL;
            }
        }
        *head = (*head)->next;
    }
    return new;
}
void extract_date(Birthday* head, Date date){
    if(head == NULL || *head == NULL)
        return;
    Birthday current, prev;
    while(*head != NULL && dateCompare((*head)->date, date) == 0){
        printf("%s\n", (*head)->name);
        current = *head;
        *head = (*head)->next;
        free(current);
    }
    if(*head == NULL)
        return;
    current = (*head)->next;
    prev = *head;
    while (current != NULL)
    {
        if(dateCompare(current->date, date) == 0)
        {
            printf("%s\n", current->name);
            prev->next = current->next;
            free(current);
            current = prev->next;
            continue;
        }
        current = current->next;
        prev = prev->next;
    }
}
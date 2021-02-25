#include "Abll.h"
#include <stdio.h>
#include <stdlib.h>

void *Abll_push(void *this, void *element)
{
    if(element == NULL)
        return this;
    ((LINK*)element)->next = NULL;
    if(this == NULL)
        return element;
    LINK *tmp = this;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = element;
    return this;
}

void *Abll_pop(void *this, void **element)
{
    if(this == NULL || ((LINK*)this)->next == NULL)
    {
        *element = this;
        return NULL;
    }
    LINK *tmp = this;
    while (tmp->next->next != NULL)
        tmp = tmp->next;
    *element = tmp->next;
    tmp->next = NULL;
    return this;
}

void *Abll_shift(void *this, void *element)
{
    if(element == NULL)
        return this;
    ((LINK*)element)->next = this;
    return element;
}

void *Abll_unshift(void *this, void **element)
{
    *element = this;
    if(this == NULL || ((LINK*)this)->next == NULL)
        return NULL;
    return ((LINK*)this)->next;
}

int Abll_size(void *this)
{
    int count = 0;
    while (this != NULL)
    {
        ++count;
        this = ((LINK*)this)->next;
    }
    return count;
}

void *AbFilter(void *this, BOOL (*FilterElement)(void*, int), int val, void **removed)
{
    *removed = NULL;
    int n = Abll_size(this);
    for(int i = 0; i < n; i++)
    {
        LINK *tmp;
        this = Abll_pop(this, &tmp);
        if(FilterElement(tmp, val) == TRUE)
            this = Abll_shift(this, tmp);
        else
            *removed = Abll_shift(*removed, tmp);
    }
    return this;
}
#ifndef ABLL_H_
#define ABLL_H_
#include <stdlib.h>

typedef struct _link
{
    struct _link *next;
} LINK;

typedef enum _bool {FALSE, TRUE} BOOL;

void *Abll_push(void *this, void *element);
void *Abll_pop(void *this, void **element);
void *Abll_shift(void *this, void *element);
void *Abll_unshift(void *this, void **element);
int Abll_size(void *this);

#endif
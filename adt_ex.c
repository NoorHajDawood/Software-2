#include "adt_ex.h"
#include <stdlib.h>
#include <assert.h>
struct _set
{
    int maxSize;
    int size;
    Element *arr;
    copy_function copyFunc;
    compare_function compareFunc;
    free_function freeFunc;
    print_function printFunc;
};

Result create(Set *dest, copy_function copyFunc, compare_function compareFunc, free_function freeFunc, print_function printFunc)
{
    *dest = (Set)malloc(sizeof(struct _set));
    assert(*dest != NULL);
    (*dest)->maxSize = 0;
    (*dest)->size = 0;
    (*dest)->arr = NULL;
    (*dest)->copyFunc = copyFunc;
    (*dest)->compareFunc = compareFunc;
    (*dest)->freeFunc = freeFunc;
    (*dest)->printFunc = printFunc;
}
Result add(Set *s, Element elm)
{
    assert(s != NULL);
    if ((*s)->size == (*s)->maxSize)
    {
        if ((*s)->maxSize == 0)
        {
            (*s)->maxSize = 8;
            (*s)->arr = (Element *)calloc((*s)->maxSize, sizeof(Element));
            // if()
            //     return Fail;
        }
        else
        {
            (*s)->maxSize = (*s)->maxSize * 2;
            (*s)->arr = (Element *)realloc((*s)->arr, (*s)->maxSize);
            // if...
            // fail;
        }
    }
    (*s)->arr[(*s)->size++] = elm;
    return Success;
}
Result copy(Set s1, Set *dest)
{
    *dest = (Set)malloc(sizeof(struct _set));
    //if ..
    //  return Fail;
    *dest = s1;
    return Success;
}
Result smallToLarge(Set *s)
{
    //Bubble Sort using compareFunc
}
void freeSet(Set *s)
{
    //free each element in (*s)->arr using freeFunc
    //then
    free((*s)->arr);
    free(*s);
}
Element elementInIndex(Set *s, int index)
{
    return (*s)->copyFunc((*s)->arr[index]);
}
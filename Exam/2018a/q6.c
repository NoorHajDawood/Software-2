#include "q6.h"
#include <stdlib.h>
struct _vector
{
    int maxSize;
    int size;
    int *arr;
};
Result create(int n, vector *v)
{
    if(n <= 0 || v == NULL)
        return Fail;
    *v = (vector)malloc(sizeof(*v));
    if(*v == NULL)
        return Fail;
    (*v)->maxSize = n;
    (*v)->size = 0;
    (*v)->arr = (int *)calloc(n, sizeof(int));
    if((*v)->arr == NULL)
    {
        free(*v);
        return Fail;
    }
    return Success;
}
Result add(vector v, int n)
{
    if(v->size == v->maxSize)
        return Fail;
    v->arr[v->size++] = n;
    return Success;
}
Result add_at(vector v, int n, int i)
{
    if(i < 0 || i >= v->maxSize)
        return Fail;
    if(v->size < i)
        i = v->size;
    for(int j=v->size++; j>i; j--)
    {
        v->arr[j] = v->arr[j-1];
    }
    v->arr[i] = n;
    return Success;
}
Result delete_at(vector v, int i)
{
    if(i < 0 || i >= v->size)
        return Fail;
    v->size--;
    for(; i<v->size; i++)
    {
        v->arr[i] = v->arr[i+1];
    }
    return Success;
}
Result element_at(vector v, int i, int *res)
{
    if(res == NULL || i < 0 || i >= v->size)
        return Fail;
    *res = v->arr[i];
    return Success;
}
Result copy(vector v, vector *v2)
{
    if(v == NULL || v2 == NULL)
        return Fail;
    *v2 = malloc(sizeof(*v2));
    if(*v2 == NULL)
        return Fail;
    for (int i = 0; i < v->size; i++)
        add(*v2, v->arr[i]);
    return Success;
}
int compare(vector v1, vector v2)
{
    if(v1 == NULL || v2 == NULL)
        return 0;
    if(v1->size != v2->size)
        return 0;
    for (int i = 0; i < v1->size; i++)
    {
        if(v1->arr[i] != v2->arr[i])
            return 0;
    }
    return 1;
}
void destory(vector v)
{
    if(v == NULL)
        return;
    free(v->arr);
    free(v);
}
#include <stdio.h>
#include <stdlib.h>
int *func(int a[], int b[])
{
    int size = 0;
    for (int i = 0; a[i] != -1; i++, size++)
        ;
    for (int i = 0; b[i] != -1; i++, size++)
        ;
    int *c = malloc(size * sizeof(int));
    size = 0;
    while (*a != -1 && *b != -1)
    {
        if (*a <= *b)
        {
            if (c[size>0?size-1:size] != *a)
                c[size++] = *a;
            a++;
        }
        else
        {
            if (c[size>0?size-1:size] != *b)
                c[size++] = *b;
            b++;
        }
    }
    while (*a != -1)
    {
        if (c[size>0?size-1:size] != *a)
        {
            c[size++] = *a;
        }
        a++;
    }
    while (*b != -1)
    {
        if (c[size>0?size-1:size] != *b)
            c[size++] = *b;
        b++;
    }
    c[size++] = -1;
    c = realloc(c, sizeof(int) * size);
    printf("%d\n",size);
    return c;
}
int main(int argc, char const *argv[])
{
    int a[] = {1, 2, 2, 2, 2, 2, 2, 10, 11, -1};
    int b[] = {2, 3, 5, 6, 6, 6, 6, 9, -1};
    int *c = func(a, b);
    while (*c != -1)
    {
        printf("%d ", *(c++));
    }
    printf("\n");
    return 0;
}

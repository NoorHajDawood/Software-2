#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

#define MAX_DIGITS  10      //Maximum digits in an int

static Element copyInt(Element e)
{
    int *newInt = malloc(sizeof(*newInt));
    if (newInt == NULL)
        return NULL;
    *newInt = *(int *)e;
    return newInt;
}

static void freeInt(Element e)
{
    free(e);
}

static bool equalInt(Element e1, Element e2)
{
    return *(int *)e1 == *(int *)e2;
}

static char *printInt(Element e)
{
    char *str = malloc(MAX_DIGITS + 1);
    if (str == NULL)
        return NULL;
    sprintf(str, "%d", *(int *)e);
    return str;
}

static bool lessThan(Element e, void* param)
{
    return *(int*)e < *(int*)param;
}

int main()
{
    Set set1 = setCreate(copyInt, freeInt, equalInt);
    Set set2 = setCreate(copyInt, freeInt, equalInt);
    for (int j = 0; j < 20; j += 2)
        setAdd(set1, &j);
    for (int j = 0; j < 12; j += 3)
        setAdd(set2, &j);

    setPrint(set1, printInt);
    setPrint(set2, printInt);

    Set unionSet = setUnion(set1, set2);
    Set intersectionSet = setIntersection(set1, set2);
    printf("The Union set is:\n");
    setPrint(unionSet, printInt);
    printf("The Intersection set is:\n");
    setPrint(intersectionSet, printInt);
    int sum=0;
    SET_FOREACH(int*, val, unionSet)
        sum += *val;
    printf("Sum of all integers in Union is:%d\n", sum);

    int threshold = 8;
    printf("Filter to less than %d\n", threshold);
    Set FilteredSet = setFilter(unionSet, lessThan, &threshold);
    setPrint(FilteredSet, printInt);
    
    setDestroy(set1);
    setDestroy(set2);
    setDestroy(unionSet);
    setDestroy(intersectionSet);
    setDestroy(FilteredSet);
    return 0;
}

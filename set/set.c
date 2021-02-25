#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"
#define EXPAND_RATE 2
#define INITIAL_SIZE 10
#define ELEMENT_NOT_FOUND -1
//Struct representing a set implemented as an array
struct set
{
    Element *elements;
    int size;
    int maxSize;
    int iterator;
    ElemCopyFunction copy;
    ElemFreeFunction free;
    ElemEqualFunction equal;
};

static SetResult expand(Set set)
{
    int newSize = EXPAND_RATE * set->maxSize;
    Element *newElements = realloc(set->elements, newSize * sizeof(Element));
    if (newElements == NULL)
        return SET_OUT_OF_MEMORY;
    set->elements = newElements;
    set->maxSize = newSize;
    return SET_SUCCESS;
}

Set setCreate(ElemCopyFunction copy, ElemFreeFunction destroy,
              ElemEqualFunction equal)
{
    assert(copy != NULL && destroy != NULL && equal != NULL);
    Set set = malloc(sizeof(*set));
    if (set == NULL)
        return NULL;
    set->elements = malloc(INITIAL_SIZE * sizeof(Element));
    if (set->elements == NULL)
    {
        free(set);
        return NULL;
    }
    set->size = 0;
    set->iterator = 0;
    set->maxSize = INITIAL_SIZE;
    set->copy = copy;
    set->free = destroy;
    set->equal = equal;
    return set;
}

static int find(Set set, Element target)
{
    for (int i = 0; i < set->size; i++)
        if (set->equal(set->elements[i], target))
            return i;
    return ELEMENT_NOT_FOUND;
}

Element setContains(Set set, Element element)
{
    assert(set != NULL && element != NULL);
    int i = find(set, element);
    return i == ELEMENT_NOT_FOUND ? NULL : set->elements[i];
}

SetResult setAdd(Set set, Element element)
{
    assert(set != NULL);
    if (element == NULL)
        return SET_NULL_ARG;
    if (setContains(set, element))
        return SET_SUCCESS;
    if (set->size == set->maxSize && expand(set) == SET_OUT_OF_MEMORY)
        return SET_OUT_OF_MEMORY;
    Element newElement = set->copy(element);
    if (newElement == NULL)
        return SET_OUT_OF_MEMORY;
    set->elements[set->size++] = newElement;
    return SET_SUCCESS;
}

SetResult setRemove(Set set, Element element)
{
    assert(set != NULL);
    if (element == NULL)
        return SET_NULL_ARG;
    int index = find(set, element);
    if (index == ELEMENT_NOT_FOUND)
        return SET_SUCCESS;
    set->free(set->elements[index]);
    set->elements[index] = set->elements[--set->size];
    set->iterator = 0;
    return SET_SUCCESS;
}

void setDestroy(Set set)
{
    assert(set != NULL);
    while (!setIsEmpty(set))
        setRemove(set, setGetFirst(set));
    free(set->elements);
    free(set);
}

static SetResult addOrDestroy(Set set, Element element)
{
    SetResult result = setAdd(set, element);
    if (result == SET_OUT_OF_MEMORY)
        setDestroy(set);
    return result;
}

static SetResult addAllOrDestroy(Set set, Set toAdd)
{
    for (int i = 0; i < toAdd->size; ++i)
        if (addOrDestroy(set, toAdd->elements[i]) == SET_OUT_OF_MEMORY)
            return SET_OUT_OF_MEMORY;
    return SET_SUCCESS;
}

Set setCopy(Set set)
{
    assert(set != NULL);
    Set newSet = setCreate(set->copy, set->free, set->equal);
    if (newSet == NULL)
        return NULL;
    if (addAllOrDestroy(newSet, set) == SET_OUT_OF_MEMORY)
        return NULL;
    newSet->iterator = set->iterator;
    return newSet;
}

static bool sameTypeSets(Set set1, Set set2)
{
    return set1->copy == set2->copy && set1->free == set2->free &&
           set1->equal == set2->equal;
}

Set setUnion(Set set1, Set set2)
{
    assert(set1 != NULL && set2 != NULL);
    assert(sameTypeSets(set1, set2));
    Set newSet = setCopy(set1);
    if (newSet == NULL)
        return NULL;
    if (addAllOrDestroy(newSet, set2) == SET_OUT_OF_MEMORY)
        return NULL;
    return newSet;
}

Set setIntersection(Set set1, Set set2)
{ //TODO
    assert(set1 != NULL && set2 != NULL);
    assert(sameTypeSets(set1, set2));
    Set newSet = setCreate(set1->copy, set1->free, set1->equal);
    SET_FOREACH(Element, element, set1){
        if(setContains(set2, element))
            setAdd(newSet, element);
    }
    return newSet;
}

void setPrint(Set set, ElemToStringFunction toString)
{ //TODO
    char *str;
    if (set && set->elements)
        for (int i = 0; i < set->size; i++)
        {
            str = toString(set->elements[i]);
            printf("%s\n", str);
            free(str);
        }
}

Element setGetFirst(Set set)
{ //TODO
    assert(set != NULL && set->elements != NULL);
    return set->elements[set->iterator = 0];
}

Element setGetNext(Set set)
{ //TODO
    assert(set != NULL && set->elements != NULL);
    return set->elements[++(set->iterator)];
}

Set setFilter(Set set, ElemConditionFunction condition, void *param)
{ //TODO
    Set filtered = setCreate(set->copy, set->free, set->equal);
    for (int i = 0; i < set->size; i++)
        if (condition(set->elements[i], param))
        {
            setAdd(filtered, set->elements[i]);
        }
    return filtered;
}

bool setIsEmpty(Set set)
{ //TODO
    assert(set != NULL);
    return set->iterator >= set->size;
}
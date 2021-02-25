#ifndef _SET_H
#define _SET_H
#include <stdbool.h>
typedef struct set *Set;
typedef enum
{
    SET_SUCCESS,
    SET_OUT_OF_MEMORY,
    SET_NULL_ARG
} SetResult;
typedef void *Element;

typedef Element (*ElemCopyFunction)(Element);
typedef void (*ElemFreeFunction)(Element);
typedef bool (*ElemEqualFunction)(Element, Element);
typedef char *(*ElemToStringFunction)(Element);
typedef bool (*ElemConditionFunction)(Element, void *param);
Set setCreate(ElemCopyFunction copy, ElemFreeFunction free,
              ElemEqualFunction equal);
Set setCopy(Set set);
void setDestroy(Set set);
SetResult setAdd(Set set, Element element);
SetResult setRemove(Set set, Element element);
Element setContains(Set set, Element element);
int setGetSize(Set set);
Set setUnion(Set set1, Set set2);
Set setIntersection(Set set1, Set set2);
Set setFilter(Set set, ElemConditionFunction condition, void *param);
void setPrint(Set set, ElemToStringFunction toString);
Element setGetFirst(Set set);
Element setGetNext(Set set);
bool setIsEmpty(Set set);
#define SET_FOREACH(Type, element, set) \
    for (Type element = setGetFirst(set); !setIsEmpty(set); element = setGetNext(set))
#endif

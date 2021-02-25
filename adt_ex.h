#ifndef _adtex_h
#define _adtex_h
typedef struct _set *Set;
typedef void* Element;
typedef enum{Fail, Success} Result;
typedef Element (*copy_function)(Element);
typedef int (*compare_function)(Element, Element);
typedef void (*free_function)(Element);
typedef void (*print_function)(Element);
typedef int (*filter_function)(Element);

Result create(Set *dest, copy_function copyFunc, compare_function compareFunc, free_function freeFunc, print_function printFunc);
Result add(Set *s, Element);
Result copy(Set s1, Set *dest);
Result smallToLarge(Set *s);
void freeSet(Set *s);
Element elementInIndex(Set *s, int index);
#endif
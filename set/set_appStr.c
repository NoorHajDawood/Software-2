// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "set.h"

// static Element copyString(Element s) {
//     char* str = malloc(strlen(s) + 1);
//     if (str == NULL) return NULL;
//     return strcpy(str, s);
// }

// static void freeString(Element s) {
//     free(s);
// }

// static bool equalString(Element s1, Element s2) {
//     return strcmp(s1, s2) == 0;
// }

// static char* printString(Element s) {
//     return copyString(s);  //printing a string is easy
// }

// static bool lessThan(Element e, void* param) {
//     return strcmp(e, param) < 0;
// }

// int main() {
//     Set set1 = setCreate(copyString, freeString, equalString);
//     Set set2 = setCreate(copyString, freeString, equalString);
//     setAdd(set1, "Hello");
//     setAdd(set1, "World");
//     setAdd(set1, "C Programming is");
//     setAdd(set1, "intellectual and Cool");

//     setAdd(set2, "Hello");
//     setAdd(set2, "Class");
//     setAdd(set2, "Global ADTS are also");
//     setAdd(set2, "intellectual and Cool");

//     setPrint(set1, printString);
//     setPrint(set2, printString);

//     Set unionSet = setUnion(set1, set2);
//     Set intersectionSet = setIntersection(set1, set2);
//     printf("The Union set is:\n");
//     setPrint(unionSet, printString);
//     printf("The Intersection set is:\n");
//     setPrint(intersectionSet, printString);
//     int sum = 0;
//     char longSentence[100] = {0};
//     SET_FOREACH(char*, val, unionSet) {
//         strcat(longSentence, val);
//         strcat(longSentence, " ");
//     }
//     printf("The sentence of all strings in the Union is:\n%s\n", longSentence);

//     char* threshold = "Ha";
//     printf("Filter to less than %s is:\n", threshold);
//     Set FilteredSet = setFilter(unionSet, lessThan, threshold);
//     setPrint(FilteredSet, printString);

//     setDestroy(set1);
//     setDestroy(set2);
//     setDestroy(unionSet);
//     setDestroy(intersectionSet);
//     setDestroy(FilteredSet);
//     return 0;
// }

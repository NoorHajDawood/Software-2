#ifndef stringADT_H
#define stringADT_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct _string *String;
typedef enum _CASE{LOWER_CASE, UPPER_CASE} CASE;

String string_create(char *);
String multString_create(String, int);
void string_destroy(String src);
int string_length(String);
char *string_chars(String);
String string_dup(String);
char string_charByIndex(String, int);
int string_findIndexByChar(String, char);
bool string_isEqual(String, String);
String string_addString(String dest, String src);
String string_copy(String dest, String src);
void string_convertCase(String, CASE);
bool string_isAllDigits(String);
int string_findString(String dest, String sub);
void string_removeString(String dest, String sub);
void string_print(String);

String StringGetFirst(String);
String StringGetNext(String);

#define STRING_FOREACH( word, str)   \
    for (String word = StringGetFirst(str); word != NULL; word = StringGetNext(str))

#endif
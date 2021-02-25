#include "stringADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct _string
{
    char *data;
    int length;
    int capacity;
    int iterator;   // index for each word , used in FOREACH
};

String string_create(char *arr)
{
    assert(arr != NULL);
    String str = (String)malloc(sizeof(*str));
    assert(str != NULL);
    str->length = 0;
    for (int i = 0; arr[i] != '\0'; i++, str->length++) //  calculate arr length
        ;
    str->capacity = str->length + 1;
    str->data = (char *)malloc(sizeof(char) * str->capacity); // initalize data's memory
    assert(str->data != NULL);
    for (int i = 0; (str->data[i] = arr[i]) != '\0'; i++) //  copy arr to data
        ;
    str->iterator = 0;
    return str;
}

String multString_create(String src, int n)
{
    assert(src != NULL);
    assert(n >= 0);
    String str = (String)malloc(sizeof(*str));
    assert(str != NULL);
    str->length = src->length * n; //  new length is old length times n
    str->capacity = str->length + 1;
    str->data = (char *)malloc(sizeof(char) * str->capacity); // initalize data
    assert(str->data != NULL);
    for (int i = 0; n--;)
    {
        for (int j = 0; (str->data[i] = src->data[j]) != '\0'; i++, j++) // copy the old data n times into new data, \0 is at new data's[new length]
            ;
    }
    return str;
}

void string_destroy(String src)
{
    assert(src != NULL);
    free(src->data); // free data
    free(src);       // then free the struct
}

int string_length(String src)
{
    assert(src != NULL);
    return src->length;
}

char *string_chars(String src)
{
    assert(src != NULL);
    return src->data;
}

String string_dup(String src)
{
    assert(src != NULL);
    return string_create(src->data);
}

char string_charByIndex(String src, int index)
{
    assert(src != NULL);
    assert(index >= 0 || index < src->length);
    return src->data[index];
}

int string_findIndexByChar(String src, char c)
{
    assert(src != NULL);
    for (int i = 0; i < src->length; i++)
    {
        if (src->data[i] == c)
            return i;
    }
    return -1;
}

bool string_isEqual(String str1, String str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);
    if (str1->length != str2->length) //  not same length, return false
        return false;
    for (int i = 0; i < str1->length; i++)
    {
        if (str1->data[i] != str2->data[i]) //  return false if something is different
            return false;
    }
    return true;
}

String string_addString(String dest, String src)
{
    assert(dest != NULL);
    assert(src != NULL);
    if (dest->capacity <= (dest->length + src->length + 1)) // dest doesn't have enough capacity
    {
        dest->capacity = dest->length + src->length + 1;
        dest->data = (char *)realloc(dest->data, sizeof(char) * dest->capacity); // increase capacity
        assert(dest->data != NULL);
    }
    for (int i = 0; (dest->data[dest->length] = src->data[i]) != '\0'; i++, dest->length++) // add src to dest // length updates accordingly
        ;
    return dest;
}

String string_copy(String dest, String src)
{
    assert(dest != NULL);
    assert(src != NULL);
    if (dest->capacity < (src->length + 1)) // dest doesn't have enough capacity
    {
        dest->capacity = src->length + 1;
        dest->length = src->length;
        dest->data[dest->length] = '\0';
        dest->data = (char *)realloc(dest->data, sizeof(char) * dest->capacity); // increase capacity
        assert(dest->data != NULL);
    }
    for (int i = 0; src->data[i] != '\0'; i++) // replace
        dest->data[i] = src->data[i];
    return dest;
}

void string_convertCase(String src, CASE flag)
{
    assert(src != NULL);
    int sign = flag == LOWER_CASE ? 1 : -1; // determine if to add or substract to the character's ASCII
    for (int i = 0; i < src->length; i++)
    {
        if (('a' <= src->data[i] && src->data[i] <= 'z' && flag == UPPER_CASE) || ('A' <= src->data[i] && src->data[i] <= 'Z' && flag == LOWER_CASE)) // if need's lower/upper case transformation
        {
            src->data[i] += sign * ('a' - 'A');
        }
    }
}

bool string_isAllDigits(String src)
{
    assert(src != NULL);
    for (int i = 0; i < src->length; i++)
    {
        if (!('0' <= src->data[i] && src->data[i] <= '9')) // return false if one isn't a number
            return false;
    }
    return true;
}

int string_findString(String dest, String sub)
{
    assert(dest != NULL);
    assert(sub);
    for (int i = 0, j; i <= (dest->length - sub->length); i++)
    {
        for (j = 0; j < sub->length; j++)
        {
            if (dest->data[i + j] != sub->data[j]) //  search sub-string
                break;
        }
        if (j == sub->length) // found then return index
            return i;
    }

    return -1;
}

void string_removeString(String dest, String sub)
{
    assert(dest != NULL);
    assert(sub != NULL);
    int i = string_findString(dest, sub); // get sub-string's index
    if (i == -1)
        return;
    for (; (dest->data[i] = dest->data[i + sub->length]) != '\0'; i++) // skip and overwrite over the sub-string
        ;
    dest->length -= sub->length; // update length
}

void string_print(String src)
{
    assert(src != NULL);
    printf("%s\n", src->data);
}

String StringGetFirst(String src)
{
    assert(src != NULL);
    src->iterator = 0; // start iterator at the start of the string
    return StringGetNext(src);
}

String StringGetNext(String src)
{
    assert(src != NULL);
    int length = 0;
    for (int i = src->iterator; src->data[i] != '\0' && (src->data[i] == ' ' || src->data[i] == '\n' || src->data[i] == '\t'); i++, src->iterator++)
        ; //  skip to the start of next word
    for (int i = src->iterator; src->data[i] != '\0' && src->data[i] != ' ' && src->data[i] != '\n' && src->data[i] != '\t'; i++, length++)
        ; //  find word's length
    if (length == 0)    // the String is empty, therefore return NULL
    {
        if (src->data[src->iterator] == '\0')
            src->iterator++;
        return NULL;
    }
    String word = (String)malloc(sizeof(*src)); // create String for the word
    word->length = length;
    word->capacity = length + 1;
    word->data = (char *)malloc(sizeof(char) * (length + 1)); // malloc an appropriate length for the word
    for (int i = src->iterator, j = 0; src->data[i] != '\0' && src->data[i] != ' ' && src->data[i] != '\n' && src->data[i] != '\t'; i++, j++)
    {
        word->data[j] = src->data[i]; // copy the word
    }
    word->data[length] = '\0';
    src->iterator += length; // iterator skips the word
    return word;    //  return the word
}
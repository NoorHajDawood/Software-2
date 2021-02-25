#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int myStrLen(char *str)
{
    int len = 0;
    while(str[len]!= '\0')
        len++;
    return len;
}
char *inputString(int initialSize)
{
    char *str;
    char c;
    int length = 0;
    str = malloc(initialSize);
    if(!str)
        return NULL;
    while((c = getc(stdin))!='\n')
    {
        if(length == initialSize)
        {
            char *tmp = malloc(initialSize+=16);
            if(!tmp)
            {
                free(str);
                return NULL;
            }
            for(int i = 0; i < length; i++)
                tmp[i] = str[i];
            free(str);
            str = tmp;
        }
        str[length++] = c;
    }
    str[length++] = '\0';
    char *result = malloc(length);
    if(!result)
    {
        free(str);
        return NULL;
    }
    for(int i = 0; i < length; i++)
                result[i] = str[i];
    free(str);
    return result;
}
int main(int argc, char const *argv[])
{
    int n;
    scanf("%d",&n);
    getc(stdin);
    char **nameArray = malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        nameArray[i] = inputString(16);
    }
    int tmpN;
    scanf("%d",&tmpN);
    getc(stdin);
    char **tmpArray = malloc(n*sizeof(char*));
    for(int i = 0; i < tmpN; i++)
    {
        tmpArray[i] = nameArray[i];
    }
    for(int i = tmpN; i < n; i++)
    {
        free(nameArray[i]);
    }
    free(nameArray);
    nameArray = tmpArray;
    n = tmpN;
    char *name = inputString(16);
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = 1;
        for(int j = 0; j < myStrLen(name); j++)
        {
            if(name[j]!=nameArray[i][j])
            {
                flag = 0;
                break;
            }
        }
        if(flag)
        {
            count++;
        }
    }
    printf("%d\n",count);
    return 0;
}

#include <stdio.h>
#include <string.h>
typedef int (*Compare)(void*, void*);
void *largest(void *e1, void *e2, void *e3, Compare compareFunc)
{
    if(compareFunc(e1, e2) > 0)
        return compareFunc(e1, e3) > 0 ? e1 : e3;
    return compareFunc(e2, e3) > 0 ? e2 : e3;
}
void **sort(void **arr, int size, Compare comp)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if(comp(arr[i],arr[j]) < 0){
                void *temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
    }
    
}
int main(int argc, char const *argv[])
{
    char str1[] = "String H";
    char str2[] = "String B";
    char str3[] = "String G";
    char str4[] = "String F";
    char str5[] = "String C";
    char str6[] = "String D";
    char *strArr[] = {str1, str2, str3, str4, str5, str6};
    //printf("%s\n", (char*)largest(str1, str2, str3, (Compare)strcmp));
    sort((void**)strArr, 6, (Compare)strcmp);
    for(int i = 0; i < 6; i++)
        printf("%s\t", strArr[i]);
    printf("\n");
    return 0;
}
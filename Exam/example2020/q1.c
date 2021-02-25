#include <stdio.h>
#define SIZE 10

void func(int array[], int size) {
    int x,y;
    if (size < 2)
        return;
    else
    {
        x = array[0];
        y = array[size-1];
        func(array+1,size-2);
        array[0] = y;
        array[size-1] = x;
    }
}
int main(int argc, char const *argv[])
{
    int numbers[SIZE] = {1,3,5,7,5,6,3,2,1,5};
    int i;
    printf("\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    func(numbers,SIZE);
    printf("\n");
    for (i = 0; i < SIZE; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    return 0;
}

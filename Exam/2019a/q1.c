#include <stdio.h>
#include <stdlib.h>
int *max_seq(int *vec, int size, int divisor)
{
    int maxIndex=0, maxCount=0, *result;
    for (int i = 0; i < size; i++)
    {
        int currentCount = 0;
        for (int j = i; j < size; j++)
        {
            if(vec[j]%divisor == 0)
                currentCount++;
            else
                break;
        }
        if(currentCount > maxCount)
        {
            maxIndex = i;
            maxCount = currentCount;
        }
    }
    result = malloc((2+maxCount)*sizeof(int));
    result[0] = maxIndex;
    result[1] = maxCount;
    for (int i = 0; i < maxCount; i++)
    {
        result[2+i] = vec[i+maxIndex];
    }
    return result;
}
void printArr(int *arr, int size)
{
    for(int i = 0; i< size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    int arr[] = {1,2,3,6,-3,12,4,-11,8,9,-6,12};
    int *res = max_seq(arr,12,3);
    printArr(res, res[1]+2);
    return 0;
}

#include <stdio.h>
#define SIZE 5
int main(int argc, char const *argv[])
{
    int x[SIZE] = {7,5,4,3,8};
    int *ptr, *head;
    int res = 0;
    int num = 0;
    int i;
    ptr = head = x;
    while(ptr - head < SIZE) {
        for (i = 0; i < (*ptr); i++)
        {
            ++res;
        }
        num += (*(head+((*ptr)%SIZE)));
        printf("\n *ptr=%d res=%d num=%d\n", *ptr, res, num);
        ++ptr;
    }
    printf("\n res=%d num=%d\n", res, num);
    return 0;
}

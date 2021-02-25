/* main.c – program that uses the queue ADT module */
#include "queue.h"
void freeInt(int* n){
    free(n);
}
int* copyInt(int*n){
    int *new = malloc(sizeof(int));
    *new = *n;
    return new;
}
int compInt(int* n1, int* n2){
    return *n1-*n2;
}
int main()
{
    int x;
    int *res;
    Queue q1 = createQueue(10,(FreeFunction)freeInt, (CopyFunction)copyInt, (CompareFunction)compInt);
    x = 5;
    enqueue(q1,(void*) &x);
    x = 10;
    enqueue(q1, (void*)&x);
    queueTop(q1, (void**)&res);
    printf("%d ", *res);
    dequeue(q1);
    queueTop(q1, (void**)&res);
    printf("%d ", *res);
    freeQueue(q1);
    return 0;
}
/* queue.c - queue ADT module implementation */
#include "queue.h"
#include <stdio.h>
struct Queue_t
{
    void* *data;
    int head, tail;
    int count, maxSize;
    FreeFunction freeFunc;
    CopyFunction copyFunc;
    CompareFunction compFunc;
};
Queue createQueue(int maxSize, FreeFunction freeFunc, CopyFunction copyFunc, CompareFunction compFunc)
{
    // TODO: complete this section yourselves
    Queue queue = malloc(sizeof(*queue));
    queue->data = malloc(sizeof(void*)*maxSize);
    queue->head = queue->tail = 0;
    queue->count = 0;
    queue->maxSize = maxSize;
    queue->freeFunc = freeFunc;
    queue->copyFunc = copyFunc;
    queue->compFunc = compFunc;
    return queue;
}
Result enqueue(Queue queue, void* data)
{
    if (queue == NULL || data == NULL)
        return BAD_ARGUMENT;
    if (isFull(queue))
        return FULL;
    queue->data[queue->tail++] = queue->copyFunc(data);
    queue->tail %= queue->maxSize;
    ++queue->count;
    return SUCCESS;
}
Result dequeue(Queue queue)
{
    if (NULL == queue)
        return BAD_ARGUMENT;
    if (TRUE == isEmpty(queue))
        return EMPTY;
    ++queue->head;
    queue->head %= queue->maxSize;
    queue->freeFunc(queue->data[queue->head-1]);
    --queue->count;
    return SUCCESS;
}
Result queueTop(Queue queue, void* *res)
{
    // TODO: complete this section yourselves
    if(queue == NULL)
        return BAD_ARGUMENT;
    if(isEmpty(queue) == TRUE)
        return EMPTY;
    //printf("%d\n", queue->data[queue->head]);
    *res = queue->copyFunc(queue->data[queue->head]);
    return SUCCESS;
}
Result contains(Queue queue, void* data, Bool *res)
{
    if (queue == NULL || res == NULL)
        return BAD_ARGUMENT;
    if (isEmpty(queue))
        return EMPTY;
    for (int i = queue->head; i != queue->tail; i = (i + 1) % queue->maxSize)
        if (queue->compFunc(queue->data[i], data) == 0)
        {
            *res = TRUE;
            return SUCCESS;
        }
    return FAIL;
}
void freeQueue(Queue queue)
{
    while (dequeue(queue) == SUCCESS)
        ;
    free(queue->data);
    free(queue);
}
Bool isEmpty(Queue queue){
    return queue->count == 0;
}
Bool isFull(Queue queue){
    return queue->count == queue->maxSize;
}
/* queue.h - queue ADT module header file */
#ifndef _queue_h
#define _queue_h
#include <stdlib.h>
#include <stdio.h>
typedef void (*FreeFunction)(void*);
typedef void* (*CopyFunction)(void*);
typedef int (*CompareFunction)(void*, void*);
typedef struct Queue_t* Queue;
typedef enum { SUCCESS, FAIL, BAD_ARGUMENT, FULL, EMPTY } Result;
typedef enum {FALSE, TRUE} Bool;
Queue createQueue(int maxSize, FreeFunction freeFunc, CopyFunction copyFunc, CompareFunction compFunc);
Bool isEmpty(Queue queue);
Bool isFull(Queue queue);
Result enqueue(Queue queue, void* data);
Result dequeue(Queue queue);
Result queueTop(Queue queue, void** res);
Result contains(Queue queue, void* data, Bool* res);
void freeQueue(Queue queue);
#endif
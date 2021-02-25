#ifndef _VECTOR_H
#define _VECTOR_H
typedef enum {Fail, Success} Result;
typedef struct _vector *vector;
Result create(int n, vector *res);
Result add(vector v, int n);
Result add_at(vector v, int n, int i);
Result delete_at(vector v, int i);
Result element_at(vector v, int i, int *res);
Result copy(vector v, vector *res);
int compare(vector v1, vector v2);
void destory(vector v);
#endif
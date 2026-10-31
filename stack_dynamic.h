#include <stdio.h>
#include <stdlib.h>
typedef struct _ntree ntree;

#define STACK_ELEM ntree*
#define STACK_ELEM_DEFAULT NULL

typedef struct _stack stack;

stack* stack_new();

stack* stack_new_with(int maxsize);

void stack_free(stack* s);

int stack_getsize(stack* s);

int stack_getmaxsize(stack* s);

void push(stack* s, STACK_ELEM elem);

STACK_ELEM pop(stack* s);

STACK_ELEM top(stack* s);

int stack_isempty(stack* s);

int stack_isfull(stack* s);

void stack_destroy(stack* s, void elem_free(STACK_ELEM));
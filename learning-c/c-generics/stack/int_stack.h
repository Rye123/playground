#ifndef _GUARD_INT_STACK_H_
#define _GUARD_INT_STACK_H_
#include <stdlib.h>

typedef struct {
    int* items;
    size_t count;  // Number of items
    size_t space;  // Allocated space
} int_stack;

typedef struct {
    int error;  // 0 for no error
    int value;
} int_stack_result;

int_stack* int_stack_new(size_t initialSpace);
void int_stack_free(int_stack* stk);

void int_stack_push(int_stack* stk, int val);
int_stack_result int_stack_pop(int_stack* stk);

#endif

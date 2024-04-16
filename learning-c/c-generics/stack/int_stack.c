#include <stdlib.h>
#include "int_stack.h"
#define DEFAULT_INITIAL_SPACE 5

int_stack* int_stack_new(size_t initialSpace)
{
    int_stack* stk = malloc(sizeof(int_stack));
    if (!stk)
        return NULL;
    stk->items = malloc(sizeof(int) * initialSpace);
    stk->count = 0;
    stk->space = initialSpace;
    return stk;
}

void int_stack_free(int_stack* stk)
{
    free(stk->items);
    free(stk);
}

void int_stack_push(int_stack* stk, int val)
{
    if (stk->count >= stk->space) {
        // Allocate more space
        size_t newSpace = stk->space * 2;
        if (newSpace == 0)
            newSpace = DEFAULT_INITIAL_SPACE;
        stk->items = realloc(stk->items, sizeof(int) * newSpace);
        stk->space = newSpace;
    }

    // Add item
    stk->items[stk->count] = val;
    stk->count += 1;
}

int_stack_result int_stack_pop(int_stack* stk)
{
    int_stack_result res;
    res.error = 1;
    res.value = 0;
    if (stk->count == 0)
        return res;

    res.error = 0;
    stk->count -= 1;
    res.value = stk->items[stk->count];
    return res;
}

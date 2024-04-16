#include <stdio.h>
#include "stack.h"

DECL_STACK(int_stack, int);

int main(int argc, char** argv)
{
    int_stack* stk = int_stack_new(0);
    if (!stk) {
        printf("Error: Error allocating stack.\n");
        exit(1);
    }
    for (size_t i = 1; i < argc; i++) {
        int val = atoi(argv[i]);
        printf("Pushing to stack: %d; Count: %lu; Space: %lu\n", val, stk->count, stk->space);
        int_stack_push(stk, val);
    }

    while (stk->count > 0) {
        int_stack_result res = int_stack_pop(stk);
        if (res.error) {
            printf("Error: Stack empty.\n");
            exit(1);
        }
        printf("stk pop: %d, Count: %lu, Space: %lu\n", res.value, stk->count, stk->space);
    }

    int_stack_result res = int_stack_pop(stk);
    if (!res.error) {
        printf("stk is not empty\n");
        exit(1);
    }
    return 0;
}

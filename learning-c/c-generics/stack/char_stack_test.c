#include <stdio.h>
#include "stack.h"

DECL_STACK(char_stack, char);

int main(int argc, char** argv)
{
    char_stack* stk = char_stack_new(0);
    if (!stk) {
        printf("Error: Error allocating stack.\n");
        exit(1);
    }
    for (size_t i = 1; i < argc; i++) {
        printf("Pushing to stack: %c; Count: %lu; Space: %lu\n", argv[i][0], stk->count, stk->space);
        char_stack_push(stk, argv[i][0]);
    }

    while (stk->count > 0) {
        char_stack_result res = char_stack_pop(stk);
        if (res.error) {
            printf("Error: Stack empty.\n");
            exit(1);
        }
        printf("stk pop: %c, Count: %lu, Space: %lu\n", res.value, stk->count, stk->space);
    }

    char_stack_result res = char_stack_pop(stk);
    if (!res.error) {
        printf("stk is not empty\n");
        exit(1);
    }
    return 0;
}

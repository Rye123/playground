#include <stdio.h>
#include "stack.h"

typedef struct _exstruct{
    int a;
    char* b;
} exstr;

exstr exstr_new(char *str)
{
    exstr s;
    s.a = atoi(str);
    s.b = str;
    return s;
}

void exstr_print(exstr s)
{
    printf("(%d, %s)", s.a, s.b);
}

DECL_STACK(exstr_stack, exstr);

int main(int argc, char **argv)
{
    exstr_stack* stk = exstr_stack_new(0);
    
    if (!stk) {
        printf("Error: Error allocating stack.\n");
        exit(1);
    }
    for (size_t i = 1; i < argc; i++) {
        exstr val = exstr_new(argv[i]);
        printf("Pushing to stack: ");
        exstr_print(val);
        printf(", Count: %lu; Space: %lu\n", stk->count, stk->space);
        exstr_stack_push(stk, val);
    }

    while (stk->count > 0) {
        exstr_stack_result res = exstr_stack_pop(stk);
        if (res.error) {
            printf("Error: Stack empty.\n");
            exit(1);
        }
        printf("stk pop: ");
        exstr_print(res.value);
        printf(", Count: %lu, Space: %lu\n", stk->count, stk->space);
    }

    exstr_stack_result res = exstr_stack_pop(stk);
    if (!res.error) {
        printf("stk is not empty\n");
        exit(1);
    }
    return 0;
}

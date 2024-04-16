#ifndef _GUARD_STACK_H_
#define _GUARD_STACK_H_
#include <stdlib.h>

#define DECL_STACK(stacktype, type)                                     \
    typedef struct {                                                    \
        size_t count, space;                                            \
        type *items;                                                    \
    } stacktype;                                                        \
                                                                        \
    typedef struct {                                                    \
        int error;                                                      \
        type value;                                                     \
    } stacktype##_result;                                               \
                                                                        \
    stacktype* stacktype##_new(size_t initialSpace)                     \
    {                                                                   \
        stacktype *stk = malloc(sizeof(stacktype));                     \
        if (!stk)                                                       \
            return NULL;                                                \
        stk->items = malloc(sizeof(type) * initialSpace);               \
        stk->count = 0;                                                 \
        stk->space = initialSpace;                                      \
        return stk;                                                     \
    }                                                                   \
                                                                        \
    void stacktype##_free(stacktype* stk)                               \
    {                                                                   \
        free(stk->items);                                               \
        free(stk);                                                      \
    }                                                                   \
                                                                        \
    void stacktype##_push(stacktype* stk, type val)                     \
    {                                                                   \
        size_t newSpace;                                                \
        if (stk->count >= stk->space) {                                 \
            newSpace = (stk->space == 0) ? 1 : (stk->space)*2;          \
            stk->items = realloc(stk->items, sizeof(type) * newSpace);  \
            stk->space = newSpace;                                      \
        }                                                               \
        stk->items[stk->count] = val;                                   \
        stk->count += 1;                                                \
    }                                                                   \
                                                                        \
    stacktype##_result stacktype##_pop(stacktype *stk)                  \
    {                                                                   \
        stacktype##_result res;                                         \
        res.error = 1;                                                  \
        if (stk->count == 0)                                            \
            return res;                                                 \
        res.error = 0;                                                  \
        stk->count -= 1;                                                \
        res.value = stk->items[stk->count];                             \
        return res;                                                     \
    }                                                                   \

#endif

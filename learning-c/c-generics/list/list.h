#ifndef _GUARD_LIST_H_
#define _GUARD_LIST_H_
#include <stdlib.h>
#define _LIST_DFLT_SZ_ 5

#define DECL_LIST(list_t, item_t)                                       \
    typedef struct {                                                    \
        item_t *items;                                                  \
        size_t len, maxLen;                                             \
    } list_t;                                                           \
                                                                        \
    typedef struct {                                                    \
        int error;                                                      \
        item_t value;                                                   \
    } list_t##_res;                                                     \
                                                                        \
    /* Create a new list. */                                            \
    list_t *list_t##_new()                                              \
    {                                                                   \
        list_t *ls = malloc(sizeof(list_t));                            \
        ls->items = malloc(sizeof(item_t) * _LIST_DFLT_SZ_);            \
        if (ls->items == NULL)                                          \
            return NULL;                                                \
        ls->len = 0;                                                    \
        ls->maxLen = _LIST_DFLT_SZ_;                                    \
        return ls;                                                      \
    }                                                                   \
                                                                        \
    /* Frees the list. */                                               \
    void list_t##_free(list_t *ls)                                      \
    {                                                                   \
        free(ls->items);                                                \
        free(ls);                                                       \
    }                                                                   \
                                                                        \
    /* Clears all elements from the list. */                            \
    void list_t##_clear(list_t *ls)                                     \
    {                                                                   \
        ls->len = 0;                                                    \
    }                                                                   \
                                                                        \
    /* Gets an element from the list. */                                \
    list_t##_res list_t##_get(list_t *ls, size_t idx)                   \
    {                                                                   \
        list_t##_res res;                                               \
        res.error = 1;                                                  \
        if (idx >= ls->len) return res;                                 \
        res.error = 0;                                                  \
        res.value = ls->items[idx];                                     \
        return res;                                                     \
    }                                                                   \
                                                                        \
    /* Inserts an element into the list. Returns 0 for failure. */      \
    int list_t##_insert(list_t *ls, size_t idx, item_t val)             \
    {                                                                   \
        if (idx > ls->len) return 0;                                    \
        if (ls->len >= ls->maxLen) {                                    \
            size_t newLen = (ls->maxLen == 0) ?                         \
                _LIST_DFLT_SZ_ : ls->maxLen * 2;                        \
            ls->items = realloc(ls->items, sizeof(item_t) * newLen);    \
            ls->maxLen = newLen;                                        \
        }                                                               \
        if (ls->items == NULL) return 0;                                \
        for (size_t i = ls->len; i > idx; i--)                          \
            ls->items[i] = ls->items[i-1];                              \
        ls->items[idx] = val;                                           \
        ls->len++;                                                      \
        return 1;                                                       \
    }                                                                   \
                                                                        \
    /* Removes an element from the list. */                             \
    list_t##_res list_t##_remove(list_t *ls, size_t idx)                \
    {                                                                   \
        list_t##_res res;                                               \
        res.error = 1;                                                  \
        if (idx >= ls->len || ls->len == 0) return res;                 \
        res.error = 0;                                                  \
        res.value = ls->items[idx];                                     \
        for (size_t i = idx + 1; i < ls->len; i++)                      \
            ls->items[i-1] = ls->items[i];                              \
        ls->len--;                                                      \
        return res;                                                     \
    }                                                                   \
                                                                        \
    /* Adds an element to end of the list. Returns 0 for failure. */    \
    int list_t##_push(list_t *ls, item_t val)                           \
    {                                                                   \
        return list_t##_insert(ls, ls->len, val);                       \
    }                                                                   \
                                                                        \
    /* Pops an element from the end of the list. */                     \
    list_t##_res list_t##_pop(list_t *ls)                               \
    {                                                                   \
        return list_t##_remove(ls, ls->len-1);                          \
    }                                                                   \
                                                                        \
    /* Pops an element from the start of the list. */                   \
    list_t##_res list_t##_dequeue(list_t *ls)                           \
    {                                                                   \
        return list_t##_remove(ls, 0);                                  \
    }                                                                   \
                                                                        \
    /* Create a new list from an array. */                              \
    list_t *list_t##_from_arr(item_t *arr, size_t arrLen) {             \
        list_t *ls = list_t##_new();                                    \
        for (size_t i = 0; i < arrLen; i++) {                           \
            if (!list_t##_push(ls, arr[i])) {                           \
                list_t##_free(ls);                                      \
                return NULL;                                            \
            }                                                           \
        }                                                               \
        return ls;                                                      \
    }                                                                   \

#endif

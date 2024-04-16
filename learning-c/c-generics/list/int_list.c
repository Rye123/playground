#include <stdlib.h>
#include "int_list.h"

int_list *int_list_new()
{
    int_list *ls = malloc(sizeof(int_list));
    ls->items = malloc(sizeof(int) * DEFAULT_MAXLEN);
    if (ls->items == NULL)
        return NULL;
    ls->len = 0;
    ls->maxLen = DEFAULT_MAXLEN;
    return ls;
}

int_list *int_list_from_arr(int *arr, size_t arrLen)
{
    int_list *ls = int_list_new();
    int err;
    for (size_t i = 0; i < arrLen; i++) {
        err = int_list_push(ls, arr[i]);
        if (err) {
            int_list_free(ls);
            return NULL;
        }
    }
    return ls;
}

void int_list_free(int_list *ls)
{
    free(ls->items);
    free(ls);
}

void int_list_clear(int_list *ls)
{
    ls->len = 0;
}

// Returns 1 if update is successful. Guarantees that there is enough space for at least 1 new element, assuming update is successful.
int _int_list_updateMaxLen(int_list *ls)
{
    if (ls->len < ls->maxLen)
        return 1;
    size_t newLen = (ls->maxLen == 0) ? DEFAULT_MAXLEN : ls->maxLen * 2;
    ls->items = realloc(ls->items, sizeof(int) * newLen);
    if (ls->items == NULL)
        return 0;
    ls->maxLen = newLen;
    return 1;
}

int_list_res int_list_get(int_list *ls, size_t idx)
{
    int_list_res res;
    res.error = 1;
    if (idx >= ls->len)
        return res;
    res.error = 0;
    res.value = ls->items[idx];
    return res;
}

int int_list_insert(int_list *ls, size_t idx, int val)
{
    if (idx > ls->len)
        return 1;
    
    if (!_int_list_updateMaxLen(ls))
        return 1;

    if (idx == ls->len) {
        ls->items[ls->len] = val;
        ls->len++;
        return 0;
    }

    // Otherwise, shift all values from idx onwards to the right
    for (size_t i = ls->len; i > idx; i--)
        ls->items[i] = ls->items[i-1];
    ls->items[idx] = val;
    ls->len++;
    return 0;
}

int int_list_push(int_list *ls, int val)
{
    return int_list_insert(ls, ls->len, val);
}

int_list_res int_list_remove(int_list *ls, size_t idx)
{
    int_list_res res;
    res.error = 1;
    if (idx >= ls->len || ls->len == 0)
        return res;
    res.error = 0;
    res.value = ls->items[idx];
    // Shift all values from (idx+1) to the left
    for (size_t i = idx + 1; i < ls->len; i++)
        ls->items[i-1] = ls->items[i];
    ls->len--;
    return res;
}

int_list_res int_list_dequeue(int_list *ls)
{
    return int_list_remove(ls, 0);
}

int_list_res int_list_pop(int_list *ls)
{
    return int_list_remove(ls, ls->len-1);
}

#ifndef _GUARD_INT_LIST_H_
#define _GUARD_INT_LIST_H_
#include <stdlib.h>
#define DEFAULT_MAXLEN 5

typedef struct {
    int *items;
    size_t len, maxLen;
} int_list;

typedef struct {
    int error;
    int value;
} int_list_res;

int_list *int_list_new();
int_list *int_list_from_arr(int *arr, size_t arrLen);
void int_list_free(int_list *ls);

void int_list_clear(int_list *ls);

int_list_res int_list_get(int_list *ls, size_t idx);

// Returns 0 if success
int int_list_push(int_list *ls, int val);
int_list_res int_list_pop(int_list *ls);
int_list_res int_list_dequeue(int_list *ls);

// Returns 0 if success
int int_list_insert(int_list *ls, size_t idx, int val);
int_list_res int_list_remove(int_list *ls, size_t idx);

#endif

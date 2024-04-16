#include <stdio.h>
#include <assert.h>
#include "int_list.h"

int main()
{
    int_list *ls;
    int testArr[] = {1, 2, 3, 4, 5};
    size_t testArrLen = 5;
    size_t testDynamicArrLen;
    size_t maxLen;
    int_list_res res;

    /* Test list_new() */
    printf("Test: list_new(): ");
    ls = int_list_new();
    assert(ls != NULL);
    assert(ls->len == 0);
    assert(ls->maxLen == DEFAULT_MAXLEN);
    // Test out of bounds access
    assert(int_list_get(ls, 0).error != 0);
    assert(int_list_get(ls, 5).error != 0);
    assert(int_list_get(ls, 7).error != 0);
    int_list_free(ls);
    printf("PASS\n");

    /* Test list_from_arr() */
    printf("Test: list_from_arr(): ");
    ls = int_list_from_arr(testArr, testArrLen);
    assert(ls != NULL);
    assert(ls->len == testArrLen);
    assert(ls->maxLen >= ls->len);
    for (size_t i = 0; i < testArrLen; i++) {
        res = int_list_get(ls, i);
        assert(res.error == 0);
        assert(res.value == testArr[i]);
    }
    int_list_free(ls);
    printf("PASS\n");

    /* Test list_push(), list_pop(), list_get() */
    printf("Test: list push/pop: ");
    ls = int_list_new();
    testDynamicArrLen = 10;
    for (size_t i = 0; i < testDynamicArrLen; i++) {
        assert(int_list_push(ls, i));
        res = int_list_get(ls, i);
        assert(res.error == 0);
        assert(res.value == i);
        assert(ls->items[i] == i);
    }
    assert(ls->len == testDynamicArrLen);
    assert(ls->maxLen >= ls->len);
    maxLen = ls->maxLen;
    for (size_t i = 0; i < testDynamicArrLen; i++) {
        res = int_list_pop(ls);
        assert(res.error == 0);
        assert(res.value == testDynamicArrLen - i - 1);
    }
    assert(ls->len == 0);
    assert(ls->maxLen == maxLen);
    int_list_free(ls);
    printf("PASS\n");

    /* Test list_push(), list_dequeue(), list_get() */
    printf("Test: list push/dequeue: ");
    ls = int_list_new(5);
    testDynamicArrLen = 10;
    for (size_t i = 0; i < testDynamicArrLen; i++) {
        int_list_push(ls, i);
        res = int_list_get(ls, i);
        assert(res.error == 0);
        assert(res.value == i);
        assert(ls->items[i] == i);
    }
    assert(ls->len == testDynamicArrLen);
    assert(ls->maxLen >= ls->len);
    maxLen = ls->maxLen;
    for (size_t i = 0; i < testDynamicArrLen; i++) {
        res = int_list_dequeue(ls);
        assert(res.error == 0);
        assert(res.value == i);
    }
    assert(ls->len == 0);
    assert(ls->maxLen == maxLen);
    int_list_free(ls);
    printf("PASS\n");
    
    /* Test list_insert() */
    printf("Test: list insertion: ");
    ls = int_list_new(5);
    assert(ls->len == 0);
    assert(!int_list_insert(ls, 1, 5)); // should not insert since out-of-bounds
    assert(ls->len == 0);

    // Test insertion into empty list ([5])
    assert(int_list_insert(ls, 0, 5));
    assert(ls->len == 1);
    assert(int_list_get(ls, 0).error == 0);
    assert(int_list_get(ls, 0).value == 5);

    // Test insertion at start ([3, 5]) (index 0)
    assert(int_list_insert(ls, 0, 3));
    assert(ls->len == 2);
    assert(int_list_get(ls, 0).error == 0);
    assert(int_list_get(ls, 0).value == 3);
    assert(int_list_get(ls, 1).error == 0);
    assert(int_list_get(ls, 1).value == 5);

    // Test insertion at end ([3, 5, 7]) (index 2)
    assert(int_list_insert(ls, 2, 7));
    assert(ls->len == 3);
    assert(int_list_get(ls, 0).error == 0);
    assert(int_list_get(ls, 0).value == 3);
    assert(int_list_get(ls, 1).error == 0);
    assert(int_list_get(ls, 1).value == 5);
    assert(int_list_get(ls, 2).error == 0);
    assert(int_list_get(ls, 2).value == 7);

    // Test insertion in middle ([3, 4, 5, 7]) (index 1)
    assert(int_list_insert(ls, 1, 4));
    assert(ls->len == 4);
    assert(int_list_get(ls, 0).error == 0);
    assert(int_list_get(ls, 0).value == 3);
    assert(int_list_get(ls, 1).error == 0);
    assert(int_list_get(ls, 1).value == 4);
    assert(int_list_get(ls, 2).error == 0);
    assert(int_list_get(ls, 2).value == 5);
    assert(int_list_get(ls, 3).value == 7);

    // Test insertion in middle ([3, 4, 5, 6, 7]) (index 3)
    assert(int_list_insert(ls, 3, 6));
    assert(ls->len == 5);
    assert(int_list_get(ls, 0).error == 0);
    assert(int_list_get(ls, 0).value == 3);
    assert(int_list_get(ls, 1).error == 0);
    assert(int_list_get(ls, 1).value == 4);
    assert(int_list_get(ls, 2).error == 0);
    assert(int_list_get(ls, 2).value == 5);
    assert(int_list_get(ls, 3).error == 0);
    assert(int_list_get(ls, 3).value == 6);
    assert(int_list_get(ls, 4).error == 0);
    assert(int_list_get(ls, 4).value == 7);
    maxLen = ls->maxLen;

    printf("PASS\n");

    /* Test list_remove() */
    printf("Test: list removal: ");
    // Test removal out of bounds (index 5, 6)
    res = int_list_remove(ls, 5);
    assert(res.error != 0);
    res = int_list_remove(ls, 6);
    assert(res.error != 0);
    assert(ls->len == 5);
    // Test removal at start  ([4, 5, 6, 7]) (index 0)
    res = int_list_remove(ls, 0);
    assert(res.error == 0);
    assert(res.value == 3);
    assert(ls->len == 4);
    // Test removal at end    ([4, 5, 6]) (index 3)
    res = int_list_remove(ls, 3);
    assert(res.error == 0);
    assert(res.value == 7);
    assert(ls->len == 3);
    // Test removal in middle ([4, 6]) (index 1)
    res = int_list_remove(ls, 1);
    assert(res.error == 0);
    assert(res.value == 5);
    assert(ls->len == 2);
    printf("PASS\n");

    /* Test list_clear() */
    printf("list clear: ");
    int_list_clear(ls);
    assert(ls->len == 0);
    assert(ls->maxLen == maxLen);
    int_list_free(ls);
    printf("PASS\n");

    return 0;
}

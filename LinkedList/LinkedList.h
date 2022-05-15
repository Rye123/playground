#include <stdio.h>
#include <stdlib.h>

typedef struct IntLinkedListNode IntLinkedListNode;

struct IntLinkedListNode {
    int value;
    IntLinkedListNode* next;
};

typedef struct IntLinkedList {
    IntLinkedListNode* head;
    IntLinkedListNode* tail;
    size_t size;
} IntLinkedList;


IntLinkedList intLinkedListNew();
IntLinkedList intLinkedListFromArray(int* array, size_t arraySize);
void intLinkedListInsert(IntLinkedList* intLinkedList, size_t i, int val);
int intLinkedListGet(IntLinkedList* intLinkedList, size_t i);
int intLinkedListRemove(IntLinkedList* intLinkedList, size_t i);
void intLinkedListFree(IntLinkedList* intLinkedList);
void __intLinkedListAllocateSpace(IntLinkedList* intLinkedList, size_t newSize);
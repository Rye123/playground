#include "LinkedList.h"


IntLinkedList intLinkedListNew() {
    IntLinkedList intLinkedList;
    intLinkedList.head = NULL;
    intLinkedList.tail = NULL;
    intLinkedList.size = 0;
    return intLinkedList;
}
IntLinkedList intLinkedListFromArray(int* array, size_t arraySize);

int intLinkedListGet(IntLinkedList* intLinkedList, size_t i) {
    // check if i is within bounds
    if (i >= intLinkedList->size) {
        fprintf(stderr, "ERROR: IntLinkedList Out of Bounds Error\n");
        exit(EXIT_FAILURE);
    }

    // iterate from start
    IntLinkedListNode* node = intLinkedList->head;
    for (int j = 0; j < i; j++) {
        node = node->next;
    }
    return node->value;
}

void intLinkedListInsert(IntLinkedList* intLinkedList, size_t i, int val) {
    size_t newSize = intLinkedList->size + 1;
    // check if i is within bounds
    if (i >= newSize) {
        fprintf(stderr, "ERROR: IntLinkedList Out of Bounds Error\n");
        exit(EXIT_FAILURE);
    }

    IntLinkedListNode* node = malloc(sizeof(IntLinkedListNode)); // allocate space for the next node
    node->value = val;
    node->next = NULL;

    // if size of linked list is 0, just add it
    if (newSize == 1) {
        intLinkedList->head = node;
        intLinkedList->tail = node;
    } else if (newSize - 1 == i) { // otherwise, if size of linked list == i, append it
        IntLinkedListNode* tail = intLinkedList->tail;
        tail->next = node; // existing tail points to tail node. tail node should now point to new node.
        intLinkedList->tail = node; // tail should point to new node.
    } else if (i == 0) {    // otherwise, if i == 0, append to front
        IntLinkedListNode* head = intLinkedList->head;
        node->next = head; // next value of new head should point to old head
        intLinkedList->head = node; // head should point to new node
    } else { // otherwise, we need to iterate to i-1, and set the new next values.
        IntLinkedListNode* prevNode = intLinkedList->head;
        for (int j = 0; j < i-1; j++) {
            prevNode = prevNode->next;
        }
        IntLinkedListNode* ithNode = prevNode->next;
        prevNode->next = node;
        node->next = ithNode;
    }

    
    intLinkedList->size = newSize;
}
int intLinkedListRemove(IntLinkedList* intLinkedList, size_t i);
void intLinkedListFree(IntLinkedList* intLinkedList) {
    // iterate through linkedlist, freeing data from the head onwards
    IntLinkedListNode* node = intLinkedList->head;
    for (int i = 0; i < intLinkedList->size; i++) {
        IntLinkedListNode* next = node->next;
        free(node);
        node = next;
    }
}
void __intLinkedListAllocateSpace(IntLinkedList* intLinkedList, size_t newSize);
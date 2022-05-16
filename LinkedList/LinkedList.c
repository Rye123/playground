#include "LinkedList.h"

/**
 * @brief Returns an empty IntLinkedList.
 * 
 * @return IntLinkedList 
 */
IntLinkedList intLinkedListNew() {
    IntLinkedList intLinkedList;
    intLinkedList.head = NULL;
    intLinkedList.tail = NULL;
    intLinkedList.size = 0;
    return intLinkedList;
}

/**
 * @brief Converts a fixed-size integer array into an IntLinkedList
 * 
 * @param A fixed size integer array
 * @param arraySize Size of integer array
 * @return IntLinkedList 
 */
IntLinkedList intLinkedListFromArray(int* array, size_t arraySize);

/**
 * @brief Returns the integer value stored at intLinkedList[i]. If it doesn't exist, throws an error.
 * 
 * @param intLinkedList 
 * @param i 
 * @return int 
 */
int intLinkedListGet(IntLinkedList* intLinkedList, size_t i) {
    // check if i is within bounds
    if (i >= intLinkedList->size)
        __intLinkedListOutOfBoundsError();

    // iterate from start
    IntLinkedListNode* node = intLinkedList->head;
    for (int j = 0; j < i; j++) {
        node = node->next;
    }
    return node->value;
}

/**
 * @brief Inserts an integer value at index i in intLinkedList.
 * 
 * @param intLinkedList 
 * @param i 
 * @param val 
 */
void intLinkedListInsert(IntLinkedList* intLinkedList, size_t i, int val) {
    size_t newSize = intLinkedList->size + 1;
    // check if i is within bounds
    if (i >= newSize)
        __intLinkedListOutOfBoundsError();

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

/**
 * @brief Removes the index at i from intLinkedList, and returns the stored value. Modifies the size.
 * 
 * @param intLinkedList 
 * @param i 
 * @return int 
 */
int intLinkedListRemove(IntLinkedList* intLinkedList, size_t i) {
    // check if i is within bounds
    if (i >= intLinkedList->size)
        __intLinkedListOutOfBoundsError();
    
    IntLinkedListNode* prev = intLinkedList->head;
    IntLinkedListNode* node = intLinkedList->head;
    
    if (i == 0) {// if it's head, update head to point to next one, then free
        intLinkedList->head = node->next;
    } else { // otherwise, iterate to previous node, update.
        for (int j = 0; j < i-1; j++) {
            prev = prev->next;
        }
        node = prev->next;
        prev->next = node->next;
        if (node->next == NULL) {
            intLinkedList->tail = node;
        }
    }

    int retValue = node->value;
    free(node);
    intLinkedList->size--;
    return retValue;
}

/**
 * @brief Frees the memory allocated for intLinkedList
 * 
 * @param intLinkedList 
 */
void intLinkedListFree(IntLinkedList* intLinkedList) {
    // iterate through linkedlist, freeing data from the head onwards
    IntLinkedListNode* node = intLinkedList->head;
    for (int i = 0; i < intLinkedList->size; i++) {
        IntLinkedListNode* next = node->next;
        free(node);
        node = next;
    }
}

void __intLinkedListOutOfBoundsError() {
    fprintf(stderr, "ERROR: IntLinkedList Out of Bounds Error\n");
    exit(EXIT_FAILURE);
}
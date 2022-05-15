#include "main.h"
#include "ArrayList/ArrayList.h"
#include "LinkedList/LinkedList.h"

void ArrayListTest() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Printing original array: [ ");
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    // Test for conversion from array to arraylist
    IntArrayList arrLs = intArrayListFromArray(arr, sizeof(arr)/sizeof(int));
    printf("Printing arrLs: [ ");
    for (int i = 0; i < arrLs.size; i++) {
        printf("%d ", intArrayListGet(&arrLs, i));
    }
    printf("]\n");

    // Test for element addition
    printf("Adding elements to end of arrLs:\n");
    int insertElems[6] = {11,12,13,14,15,16};
    for (int i = 0; i < sizeof(insertElems)/sizeof(int); i++){
        intArrayListInsert(&arrLs, arrLs.size, insertElems[i]);
        printf("Inserted %d at end of arrLs, arrLs.size = %lu, arrLs.__allocatedSize = %lu\n", insertElems[i], arrLs.size, arrLs.__allocatedSize);
    }
    
    intArrayListInsert(&arrLs, 2, 66);
    printf("Inserted 66 at index 2 of arrLs, arrLs.size = %lu, arrLs.__allocatedSize = %lu\n", arrLs.size, arrLs.__allocatedSize);
    printf("Printing new arrLs: [ ");
    for (int i = 0; i < arrLs.size; i++) {
        printf("%d ", intArrayListGet(&arrLs, i));
    }
    printf("]\n");

    // Test for element removal
    printf("Removing 3 elements from end of arrLs: \n");
    for (int i = 0; i < 2; i++) {
        int removed = intArrayListRemove(&arrLs, arrLs.size-1);
        printf("Removed %d from end of arrLs, arrLs.size = %lu, arrLs.__allocatedSize = %lu\n", removed, arrLs.size, arrLs.__allocatedSize);
    }
    printf("Printing new arrLs: [ ");
    for (int i = 0; i < arrLs.size; i++) {
        printf("%d ", intArrayListGet(&arrLs, i));
    }
    printf("]\n");
    printf("Removing element from index 2:\n");
    int removed = intArrayListRemove(&arrLs, 2);
    printf("Removed %d from end of arrLs, arrLs.size = %lu, arrLs.__allocatedSize = %lu\n", removed, arrLs.size, arrLs.__allocatedSize);
    printf("Printing new arrLs: [ ");
    for (int i = 0; i < arrLs.size; i++) {
        printf("%d ", intArrayListGet(&arrLs, i));
    }
    printf("]\n");

    // Error Testing
    
    // printf("Testing access of out-of-bound index:\n");
    // printf("%d\n", intArrayListGet(&arrLs, 69));
    // printf("Testing access of out-of-bound index exactly at size:\n");
    // printf("%d\n", intArrayListGet(&arrLs, arrLs.size));
    // printf("Testing access of negative index: \n");
    // printf("%d\n", intArrayListGet(&arrLs, -1));
    // printf("Testing insertion to out-of-bound index.\n");
    // intArrayListInsert(&arrLs, 42, 5);
    // printf("Testing removal of out-of-bound index:\n");
    // printf("%d\n", intArrayListRemove(&arrLs, arrLs.size));
    
    
    intArrayListFree(&arrLs);
}

void ArrayListTest2() {
    // Initialise empty ArrayList
    IntArrayList arrLs = intArrayListNew();
    intArrayListInsert(&arrLs, arrLs.size, 5);
    printf("%d\n", intArrayListGet(&arrLs, 0));
    intArrayListFree(&arrLs);
}

void reportLinkedListData(IntLinkedList* intLinkedList) {
    printf("PRINTING LINKEDLIST DATA: \n");
    printf("HEAD ADDRESS: 0x%p\n", intLinkedList->head);
    printf("TAIL ADDRESS: 0x%p\n", intLinkedList->tail);
    printf("SIZE: %lu\n", intLinkedList->size);
    printf("Printing List: \n[ ");
    for(int i = 0; i < intLinkedList->size; i++) {
        printf("%d ", intLinkedListGet(intLinkedList, i));
    }
    printf("]\n\n");
}

void LinkedListTest() {
    IntLinkedList lnkLs = intLinkedListNew();
    printf("Initialised list. ");
    reportLinkedListData(&lnkLs);

    intLinkedListInsert(&lnkLs, 0, 5);
    printf("Added 5 to index 0. ");
    reportLinkedListData(&lnkLs);

    intLinkedListInsert(&lnkLs, 1, 6);
    printf("Added 6 to index 1. ");
    reportLinkedListData(&lnkLs);

    intLinkedListInsert(&lnkLs, 0, 7);
    printf("Added 7 to index 0. ");
    reportLinkedListData(&lnkLs);

    intLinkedListInsert(&lnkLs, 1, 3);
    printf("Added 3 to index 1. ");
    reportLinkedListData(&lnkLs);

    intLinkedListInsert(&lnkLs, 0, 9);
    printf("Added 9 to index 0. ");
    reportLinkedListData(&lnkLs);

    // printf("Testing erroneous index.\n");
    // intLinkedListInsert(&lnkLs, lnkLs.size+1, 1);
    
    intLinkedListFree(&lnkLs);

}


int main() {
    LinkedListTest();
    return 0;
}
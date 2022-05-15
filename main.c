#include "main.h"
#include "ArrayList/ArrayList.h"


void ArrayListTest() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Printing original array: [ ");
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");

    // Test for conversion from array to arraylist
    IntArrayList arrLs = arrayToIntArrayList(arr, sizeof(arr)/sizeof(int));
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

int main() {
    ArrayListTest();
    return 0;
}
#include "ArrayList.h"

/**
 * @brief Converts a fixed-size integer array into an IntArrayList
 * 
 * @param array A fixed size integer array
 * @param arraySize Size of integer array
 * @return IntArrayList 
 */
IntArrayList arrayToIntArrayList(int* array, size_t arraySize) {
    IntArrayList intArrayList;
    intArrayList.__allocatedSize = arraySize;
    intArrayList.size = arraySize;
    intArrayList.contents = (int*) malloc(sizeof(int) * arraySize);
    for (int i = 0; i < intArrayList.size; i++) {
        intArrayList.contents[i] = array[i];
    }
    return intArrayList;
}

/**
 * @brief Returns the integer value stored at intArrayList[i]. If it doesn't exist, throws an error.
 * 
 * @param intArrayList
 * @param i Index of intArrayList to get
 * @return int 
 */
int intArrayListGet(IntArrayList* intArrayList, size_t i) {
    if (i < intArrayList->size)
        return intArrayList->contents[i];
    fprintf(stderr, "ERROR: IntArrayList Out of Bounds Error\n");
    exit(EXIT_FAILURE);
}

/**
 * @brief Inserts an integer value at index i in intArrayList.
 * 
 * @param intArrayList 
 * @param i Index to add value in
 * @param value
 */
void intArrayListInsert(IntArrayList* intArrayList, size_t i, int value) {
    size_t newSize = intArrayList->size + 1;
    // ensure index is within bounds
    if (i >= newSize) {
        fprintf(stderr, "ERROR: IntArrayList Out of Bounds Error\n");
        exit(EXIT_FAILURE);
    }

    // check if arrayList already has space. allocate if necessary
    if (intArrayList->__allocatedSize < newSize) { 
        size_t newAllocatedSize = intArrayList->__allocatedSize * 2;
        __intArrayListAllocateSpace(intArrayList, newAllocatedSize);
    }

    // add the value accordingly
    if (i == newSize-1) { // value is appended
        intArrayList->contents[i] = value;
    } else { // shift all values from i onwards right, then put the value in
        for (int j = newSize-1; j > i; j--) {
            intArrayList->contents[j] = intArrayList->contents[j-1];
        }
        intArrayList->contents[i] = value;
    }

    // set the new size of the arrayList
    intArrayList->size = newSize;
}

/**
 * @brief Removes the index at i from intArrayList, and returns the stored value. Modifies the size.
 * 
 * @param intArrayList 
 * @param i 
 * @return int 
 */
int intArrayListRemove(IntArrayList* intArrayList, size_t i) {

}

/**
 * @brief Frees the memory allocated for intArrayList
 * 
 * @param intArrayList 
 */
void intArrayListFree(IntArrayList* intArrayList) {
    free(intArrayList->contents);
}

void __intArrayListAllocateSpace(IntArrayList* intArrayList, size_t newSize) {
    int* newContents = realloc(intArrayList->contents, newSize);
    intArrayList->contents = newContents;
    intArrayList->__allocatedSize = newSize;
}
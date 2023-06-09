#include "ArrayList.h"

/**
 * @brief Returns an empty IntArrayList
 * 
 * @return IntArrayList 
 */
IntArrayList intArrayListNew() {
    IntArrayList intArrayList;
    intArrayList.__elementSize = sizeof(int);
    intArrayList.__allocatedSize = 1; // can contain at least one element before reallocation
    intArrayList.contents = (int*) malloc(intArrayList.__elementSize * intArrayList.__allocatedSize);
    intArrayList.size = 0;
    return intArrayList;
}

/**
 * @brief Converts a fixed-size integer array into an IntArrayList
 * 
 * @param array A fixed size integer array
 * @param arraySize Size of integer array
 * @return IntArrayList 
 */
IntArrayList intArrayListFromArray(int* array, size_t arraySize) {
    IntArrayList intArrayList;
    intArrayList.__elementSize = sizeof(int);
    intArrayList.__allocatedSize = arraySize;
    intArrayList.size = arraySize;
    intArrayList.contents = (int*) malloc(intArrayList.__elementSize * intArrayList.__allocatedSize);
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
    if (i >= intArrayList->size)
        __intArrayListOutOfBoundsError();
    return intArrayList->contents[i];
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
    if (i >= newSize)
        __intArrayListOutOfBoundsError();

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
    size_t newSize = intArrayList->size - 1;
    
    // ensure index is within bounds
    if (i >= intArrayList->size)
        __intArrayListOutOfBoundsError();

    // if i == newSize, we can just skip to modifying the size. 
    // otherwise, we need to shift elems after i leftward
    int returnValue = intArrayList->contents[i];
    if (i != newSize) {
        for (int j = i; j < newSize; j++) {
            intArrayList->contents[j] = intArrayList->contents[j+1];
        }
    }
    intArrayList->size = newSize;
    return returnValue;
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
    int* newContents = realloc(intArrayList->contents, newSize * intArrayList->__elementSize);
    intArrayList->contents = newContents;
    intArrayList->__allocatedSize = newSize;
}

void __intArrayListOutOfBoundsError() {
    fprintf(stderr, "ERROR: IntArrayList Out of Bounds Error\n");
    exit(EXIT_FAILURE);
}
#include <stdio.h>
#include <stdlib.h>

typedef struct IntArrayList {
    int* contents;
    size_t size;
    size_t __elementSize;
    size_t __allocatedSize;
} IntArrayList;

IntArrayList intArrayListNew();
IntArrayList intArrayListFromArray(int* array, size_t arraySize);
int intArrayListGet(IntArrayList* intArrayList, size_t i);
void intArrayListInsert(IntArrayList* intArrayList, size_t i, int value);
int intArrayListRemove(IntArrayList* intArrayList, size_t i);
void intArrayListFree(IntArrayList* intArrayList);
void __intArrayListAllocateSpace(IntArrayList* intArrayList, size_t newSize);

void __intArrayListOutOfBoundsError();
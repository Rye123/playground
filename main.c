#include "main.h"
#include "ArrayList/ArrayList.h"

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Printing contents of original array:\n");
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) {
        printf("%d\n", arr[i]);
    }
    printf("\n");

    IntArrayList arrayList = arrayToIntArrayList(arr, sizeof(arr)/sizeof(int));
    printf("Printing contents of original arrayList:\n");
    for (int i = 0; i < arrayList.size; i++) {
        printf("%d\n", intArrayListGet(&arrayList, i));
    }
    printf("\n");

    intArrayListInsert(&arrayList, arrayList.size, 6);
    intArrayListInsert(&arrayList, arrayList.size, 7);
    intArrayListInsert(&arrayList, 2, 8);
    intArrayListInsert(&arrayList, arrayList.size, 9);
    printf("Printing contents of new arrayList:\n");
    for (int i = 0; i < arrayList.size; i++) {
        printf("%d, ArrayList Size: %lu, ArrayList Allocated Size: %lu\n", intArrayListGet(&arrayList, i), arrayList.size, arrayList.__allocatedSize);
    }
    printf("\n");

    printf("Removing elements:\n");
    int removed = intArrayListRemove(&arrayList, arrayList.size-1);
    printf("Removed %d, new ArrayList Size: %lu, new ArrayList Allocated Size: %lu\n", removed, arrayList.size, arrayList.__allocatedSize);
    removed = intArrayListRemove(&arrayList, arrayList.size-1);
    printf("Removed %d, new ArrayList Size: %lu, new ArrayList Allocated Size: %lu\n", removed, arrayList.size, arrayList.__allocatedSize);
    removed = intArrayListRemove(&arrayList, 0);
    printf("Removed %d, new ArrayList Size: %lu, new ArrayList Allocated Size: %lu\n", removed, arrayList.size, arrayList.__allocatedSize);
    removed = intArrayListRemove(&arrayList, 3);
    printf("Removed %d, new ArrayList Size: %lu, new ArrayList Allocated Size: %lu\n", removed, arrayList.size, arrayList.__allocatedSize);
    printf("Printing contents of new arrayList:\n");
    for (int i = 0; i < arrayList.size; i++) {
        printf("%d, ArrayList Size: %lu, ArrayList Allocated Size: %lu\n", intArrayListGet(&arrayList, i), arrayList.size, arrayList.__allocatedSize);
    }
    printf("\n");

    intArrayListFree(&arrayList);
    return 0;
}
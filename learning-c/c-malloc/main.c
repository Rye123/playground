#include <stdio.h>

#include <unistd.h>
#include <assert.h>

typedef struct memblock {
  size_t size;
  int free;
  struct memblock* next;
} memblock;

#define MEMBLOCKSIZE sizeof(struct memblock)

void* MEMBLOCKHEAD = NULL;
void* MEMBLOCKTAIL = NULL;

/**
Returns a pointer to a new memblock of the given size.
- If allocation failed, returns NULL.
 */
memblock* newMemblock(size_t size)
{
  memblock* newBlock = (memblock*) sbrk(0);
  void *req = sbrk(MEMBLOCKSIZE + size);
  if (req == (void*) -1)
    return NULL;
  assert((void*) newBlock == req);

  newBlock->size = size;
  newBlock->free = 0;
  newBlock->next = NULL;

  // Set tail of linked list accordingly
  memblock* previousTail = MEMBLOCKTAIL;
  if (previousTail != NULL)
    previousTail->next = newBlock;
  MEMBLOCKTAIL = newBlock;
  
  return MEMBLOCKTAIL;
}

/**
Returns the memblock associated with a pointer.
 */
memblock* getMemblockFromPtr(void* ptr)
{
  return (memblock *) ptr - MEMBLOCKSIZE;
}

/**
Returns an available memblock, or a new one if no freed memblock with the appropriate size exists.
 */
memblock* getAvailableMemblock(size_t size)
{
  if (MEMBLOCKHEAD == NULL) {
    MEMBLOCKHEAD = newMemblock(size);
    return MEMBLOCKHEAD;
  }
  
  // Iterate until we find sufficient space or find a NULL
  memblock* curBlock = MEMBLOCKHEAD;
  
  while (curBlock != NULL) {
    if (curBlock->free == 1 && curBlock->size <= size) {
      curBlock->free = 0;
      return curBlock;
    }
    curBlock = curBlock->next;
  }

  return newMemblock(size);
}
  
/**
Frees a given pointer.
 */
void free(void* ptr)
{
  memblock* block = getMemblockFromPtr(ptr);
  block->free = 1;
}

/**
Allocates `size` bytes of memory, and returns a pointer to the location.
 */
void* malloc(size_t size)
{
  memblock* block = getAvailableMemblock(size);
  return (block + MEMBLOCKSIZE);
}

void printArr(int* arr, size_t sz)
{
  printf("[");
  for (int i = 0; i < sz-1; i++) {
    printf("%d, ", *(arr + i));
  }
  printf("%d]\n", *(arr + sz - 1));
}

int main()
{
  void* initialPtr = sbrk(0);
  int bufSz = 5;
  int* testPtr = malloc(bufSz * sizeof *testPtr);
  *testPtr = 5;
  *(testPtr + 1) = 6;
  *(testPtr + 2) = 7;
  *(testPtr + 3) = 8;
  *(testPtr + 4) = 9;

  printArr(testPtr, bufSz);

  int bufSz2 = 3;
  int* testPtr2 = malloc(bufSz2 * sizeof *testPtr2);
  *testPtr2 = 1;
  *(testPtr2 + 1) = 2;
  *(testPtr2 + 2) = 3;
  printArr(testPtr2, bufSz2);

  free(testPtr);

  int bufSz3 = 2;
  int* testPtr3 = malloc(bufSz3 * sizeof *testPtr3);
  testPtr3[0] = 9;
  testPtr3[1] = 8;
  testPtr3[2] = 7;

  printArr(testPtr3, bufSz3);

  int bufSz4 = 6;
  int* testPtr4 = malloc(bufSz4 * sizeof *testPtr4);
  testPtr4[0] = 2;
  testPtr4[1] = 4;
  testPtr4[2] = 6;
  testPtr4[3] = 8;
  testPtr4[4] = 10;
  testPtr4[5] = 12;
  printArr(testPtr4, bufSz4);

  void* curPtr = sbrk(0);
  int diff = (curPtr - initialPtr) * sizeof(int);
  printf("Size: %d\n", diff);
  
  free(testPtr2);
  free(testPtr3);
  free(testPtr4);

  int bufSz5 = 1;
  int* testPtr5 = malloc(bufSz5 * sizeof *testPtr5);
  testPtr5[0] = 2;
  printArr(testPtr5, bufSz5);
  free(testPtr5);
  return 0;
}
  

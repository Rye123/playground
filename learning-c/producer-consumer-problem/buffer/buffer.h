/* buffer.h */
#include <unistd.h>
#include <stdio.h> // for printf
#include <semaphore.h> // for semaphores
#include <pthread.h> // for mutex

typedef int buffer_item;
#define BUFFER_SIZE 5
#define BUFFER_ITEM_SIZE sizeof(buffer_item)

void buffer_init();

int insert_item(int buffer_item);
int remove_item(int* buffer_item);

void print_buffer_state();
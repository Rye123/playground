/* buffer.h */
#include <stdio.h> // for printf

typedef int buffer_item;
#define BUFFER_SIZE 5
#define BUFFER_ITEM_SIZE sizeof(buffer_item)

int insert_item(int buffer_item);
int remove_item(int* buffer_item);

void print_buffer_state();
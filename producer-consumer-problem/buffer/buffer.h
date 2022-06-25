/* buffer.h */
#define BUFFER_SIZE 5

typedef int buffer_item;
#define BUFFER_ITEM_SIZE sizeof(buffer_item)

int insert_item(int buffer_item);
int remove_item(int* buffer_item);
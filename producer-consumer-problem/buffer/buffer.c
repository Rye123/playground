#include "./buffer.h"

buffer_item buffer[BUFFER_SIZE];

int read_index = 0;
int write_index = 0;

/**
 * @brief Inserts an item into the buffer
 * 
 * @param item buffer_item
 * @return int 0 if successful, -1 otherwise
 */
int insert_item(buffer_item item)
{
    // CRITICAL SECTION START
    buffer[write_index] = item;
    write_index = (write_index + 1) % BUFFER_SIZE;
    // CRITICAL SECTION END
    return 0;
    //return -1;
}

/**
 * @brief Removes an item from the buffer, placing it in item
 * 
 * @param item buffer_item
 * @return int 0 if successful, -1 otherwise
 */
int remove_item(buffer_item *item)
{
    return -1;
}

/**
 * @brief Reports the buffer state
 */
void print_buffer_state()
{
    printf("[");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i != 0)
            printf(", ");
        printf("%d", buffer[i]);
    }
    printf("]\n");
}
#include "./buffer.h"

buffer_item buffer[BUFFER_SIZE];

int read_index = 0;
int write_index = 0;
sem_t  read_sem;
sem_t write_sem;
pthread_mutex_t read_mutex;
pthread_mutex_t write_mutex;

void buffer_init()
{
    pthread_mutex_init(&read_mutex,  NULL);
    pthread_mutex_init(&write_mutex, NULL);
    //sem_post(&write_sem); // start writing
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }
    sem_init(&read_sem,  0, 0);
    sem_init(&write_sem, 0, BUFFER_SIZE);
}

/**
 * @brief Inserts an item into the buffer
 * 
 * @param item buffer_item
 * @return int 0 if successful, -1 otherwise
 */
int insert_item(buffer_item item)
{
    pthread_mutex_lock(&write_mutex); // make sure no other producer threads can write
    sem_wait(&write_sem); // wait until can write
    // CRITICAL SECTION START
    print_buffer_state();
    buffer_item writeVal = buffer[write_index];
    if (writeVal && writeVal != -1) { // writing to valid value
        // CRITICAL SECTION END
        sem_post(&read_sem);
        pthread_mutex_unlock(&write_mutex); // release lock on this CS
        return -1;
    }
    buffer[write_index] = item;
    write_index = (write_index + 1) % BUFFER_SIZE;
    // CRITICAL SECTION END
    sem_post(&read_sem);  // notify can read
    pthread_mutex_unlock(&write_mutex); // release lock on this CS
    return 0;
}

/**
 * @brief Removes an item from the buffer, placing it in item
 * 
 * @param item buffer_item
 * @return int 0 if successful, -1 otherwise
 */
int remove_item(buffer_item *item)
{
    pthread_mutex_lock(&read_mutex); // make sure no other consumer threads can write
    sem_wait(&read_sem); // wait until can read
    // CRITICAL SECTION START
    print_buffer_state();
    buffer_item readVal = buffer[read_index];
    if (!readVal || readVal == -1) { // tried to read invalid value
        // CRITICAL SECTION END
        sem_post(&write_sem); // free write_sem
        pthread_mutex_unlock(&read_mutex); // release lock on this CS
        return -1;
    }
    *item = readVal;
    buffer[read_index] = -1;
    read_index = (read_index + 1) % BUFFER_SIZE;
    // CRITICAL SECTION END
    sem_post(&write_sem);
    pthread_mutex_unlock(&read_mutex); // release lock on this CS
    return 0;
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
        if(!buffer[i] || buffer[i] == -1)
            printf("-");
        else
            printf("%d", buffer[i]);
    }
    printf("]\n");
}
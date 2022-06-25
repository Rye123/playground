#include "./main.h"

void *producer(void *param)
{
    buffer_item item;

    while(TRUE) {
        // sleep for random period of time
        sleep(rand() % THREADSLEEP_MAX);

        // generate random number
        item = rand();
        if (insert_item(item) == 0) {
            printf("Producer: Produced item %d\n", item);
        } else {
            printf("Producer: Error condition");
        }
    }
}

void *consumer(void *param)
{
    buffer_item item;

    while(TRUE) {
        // sleep for random period of time
        sleep(rand() % THREADSLEEP_MAX);

        // generate random number
        if (remove_item(&item) == 0) {
            printf("Consumer: Consumed item %d\n", item);
        } else {
            printf("Consumer: Error condition");
        }
    }
}

int main(int argc, char** argv)
{
    /* 1. Get command line arguments:
        - argv[1]: How long to sleep before terminating main
        - argv[2]: Number of producer threads
        - argv[3]: Number of consumer threads
    */

    /* 2. Initialise buffer */

    /* 3. Create producer thread(s) */

    /* 4. Create consumer thread(s) */

    /* 5. Sleep */

    /* 6. Exit */

    return 0;
}
#include "./main.h"

void *producer(void *param)
{
    buffer_item item;

    while(TRUE) {
        // sleep for random period of time
        sleep(rand() % THREADSLEEP_MAX);

        // generate random number
        item = rand();
        printf("Producer: Trying to produce %d\n", item);
        if (insert_item(item) == 0) {
            printf("Producer: Produced item %d\n", item);
        } else {
            fprintf(stderr, "Producer: Error condition\n");
        }
    }
}

void *consumer(void *param)
{
    buffer_item item;

    while(TRUE) {
        // sleep for random period of time
        sleep(rand() % THREADSLEEP_MAX);
        printf("Consumer: Trying to consume the next item.\n");

        // generate random number
        if (remove_item(&item) == 0) {
            printf("Consumer: Consumed item %d\n", item);
        } else {
            fprintf(stderr, "Consumer: Error condition\n");
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
    if (argc < 4) {
        printf("Not enough commands -- need 3, was provided %d.\n", argc-1);
        return EXIT_FAILURE;
    }
    int termination_delay = atoi(argv[1]);
    int producer_count = atoi(argv[2]);
    int consumer_count = atoi(argv[3]);

    printf("Main: Initialising program with %d producers, %d consumers, to end in %d seconds.\n\n", producer_count, consumer_count, termination_delay);

    /* 2. Initialisation */

    /* 3. Create producer thread(s) */
    pthread_t *producers = malloc(BUFFER_ITEM_SIZE * producer_count);
    for (int i = 0; i < producer_count; i++) {
        if (pthread_create(&producers[i], NULL, producer, NULL) != 0)
            perror("Main: Producer thread creation error.");
        printf("Main: Created producer %d.\n", i);
    }

    /* 4. Create consumer thread(s) */
    pthread_t *consumers = malloc(BUFFER_ITEM_SIZE * consumer_count);
    for (int i = 0; i < consumer_count; i++) {
        if (pthread_create(&consumers[i], NULL, consumer, NULL) != 0)
            perror("Main: Consumer thread creation error.");
        printf("Main: Created consumer %d.\n", i);
    }

    /* 5. Sleep */
    buffer_init();
    sleep(termination_delay);
    /* 6. Exit */
    // clean up threads
    printf("\n\nMain: Killing Threads now.\n");
    for (int i = 0; i < producer_count; i++) {
        pthread_cancel(producers[i]);
        printf("Main: Killed producer %d.\n", i);
    }
    for (int i = 0; i < consumer_count; i++) {
        pthread_cancel(consumers[i]);
        printf("Main: Killed consumer %d.\n", i);
    }

    printf("Current Buffer State: ");
    print_buffer_state();

    return EXIT_SUCCESS;
}
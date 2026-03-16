#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void print_buffer() {
    printf("Buffer: [ ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == in && i == out && buffer[i] != 0) {
            printf("P/C-%d ", buffer[i]);  // Mark the item being produced and consumed
        } else if (buffer[i] != 0) {
            printf("%d ", buffer[i]);
        }
    }
    printf("]\n");
}

void *producer(void *arg)
{
    int item;
    for(int i = 0; i < 10; i++)
    {
        item = i + 1;

        sem_wait(&empty);   // Wait if buffer is full
        sem_wait(&mutex);   // Enter critical section

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        print_buffer();  // Print buffer status after producing an item

        sem_post(&mutex); // Exit critical section
        sem_post(&full);  // Signal that there is a new item to consume
    }
}

void *consumer(void *arg)
{
    int item;
    for(int i = 0; i < 10; i++)
    {
        sem_wait(&full);    // Wait if buffer is empty
        sem_wait(&mutex);   // Enter critical section

        item = buffer[out];
        printf("Consumed: %d\n", item);
        buffer[out] = 0;    // Mark the slot as empty
        out = (out + 1) % BUFFER_SIZE;

        print_buffer();  // Print buffer status after consuming an item

        sem_post(&mutex); // Exit critical section
        sem_post(&empty); // Signal that there is an empty slot available for producer
    }
}

int main()
{
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);  // Initialize 'empty' semaphore with buffer size
    sem_init(&full, 0, 0);  // No items are in the buffer initially
    sem_init(&mutex, 0, 1); // Mutex for mutual exclusion on buffer

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

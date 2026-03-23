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
            printf("P/C-%d ", buffer[i]); 
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
        sem_wait(&empty);  
        sem_wait(&mutex);  
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        print_buffer();  
        sem_post(&mutex); 
        sem_post(&full);  
    }
}
void *consumer(void *arg)
{
    int item;
    for(int i = 0; i < 10; i++)
    {
        sem_wait(&full);   
        sem_wait(&mutex);  
        item = buffer[out];
        printf("Consumed: %d\n", item);
        buffer[out] = 0; 
        out = (out + 1) % BUFFER_SIZE;
        print_buffer(); 
        sem_post(&mutex);
        sem_post(&empty);
    }
}
int main()
{
    pthread_t p, c;
    sem_init(&empty, 0, BUFFER_SIZE); 
    sem_init(&full, 0, 0);  
    sem_init(&mutex, 0, 1); 
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}

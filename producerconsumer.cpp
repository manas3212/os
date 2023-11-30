#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>   

#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 3
#define N 5
#define NUM_ITEMS 5
sem_t mutex;
sem_t empty;
sem_t full;
int buffer[N];
int in = 0;
int out = 0;
int items_produced = 0;
int items_consumed = 0;
void displayBuffer()
{
    printf("\n---------------Buffer: [");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", buffer[i]);
    }
    printf("]\n");
}
void *producer(void *arg)
{
    int item;
    while (items_produced < NUM_ITEMS)
    {
        item = rand() % 100;
        displayBuffer();
        printf("Producer is trying to produce item %d\n", item);
        sem_wait(&empty);
        sem_wait(&mutex);
        if (((in + 1) % N) == out)
        {
            printf("\n ---------------The buffer is full---------------------\n");
            displayBuffer();
        }
        buffer[in] = item;
        in = (in + 1) % N;
        printf("Producer produced item %d\n", item);
        items_produced++;
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}
void *consumer(void *arg)
{
    int item;
    while (item != -1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        buffer[out] = -1;
        out = (out + 1) % N;
        printf("Consumer consumed item %d\n", item);
        items_consumed++;
        if (in == out)
        {
            printf("\n ---------------The buffer is Empty---------------------\n");
            displayBuffer();
        }
        sem_post(&mutex);
        sem_post(&empty);
        usleep(rand() % 100000);
    }
    pthread_exit(NULL);
}
int main()
{
    srand(time(NULL));
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

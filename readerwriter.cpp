#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

sem_t mutex, write_mutex;
int reader_count = 0, data = 0;

void *reader(void *arg) {
    int reader_id = *(int *)arg;
    while (1) {
        // Entering critical section
        sem_wait(&mutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&write_mutex);
        }
        sem_post(&mutex);
        
        // Reading
        printf("Reader %d is reading data: %d\n", reader_id, data);
        
        // Exiting critical section
        sem_wait(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&write_mutex);
        }
        sem_post(&mutex);

        // Sleep to simulate reading time
        usleep(rand() % 1000000);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *(int *)arg;
    while (1) {
        // Writer acquiring write_mutex for exclusive access
        sem_wait(&write_mutex);

        // Writing
        data++;
        printf("Writer %d is writing data: %d\n", writer_id, data);

        // Releasing write_mutex
        sem_post(&write_mutex);

        // Sleep to simulate writing time
        usleep(rand() % 1000000);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    pthread_t reader_threads[NUM_READERS];
    pthread_t writer_threads[NUM_WRITERS];

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}

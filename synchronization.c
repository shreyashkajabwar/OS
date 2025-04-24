#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>

#define MAX 50

int sleepMod = 5;
int readCount = 0;
int isSync = 1; // Default to synchronous mode

sem_t readAccess, bookAccess;

void *reader_func(void *);
void *writer_func(void *);

pthread_t readers_t[MAX], writers_t[MAX];

int main() {
    srand(time(0));

    int readers, writers, mode;

    printf("Choose mode: 1 for Synchronous, 2 for Asynchronous: ");
    scanf("%d", &mode);
    isSync = (mode == 1) ? 1 : 0;

    printf("Number of readers (max 50): ");
    scanf("%d", &readers);
    printf("Number of writers (max 50): ");
    scanf("%d", &writers);

    if (readers > 5)
        sleepMod = readers;

    sem_init(&readAccess, 0, 1);
    sem_init(&bookAccess, 0, 1);

    int reader_ids[MAX], writer_ids[MAX];

    for (int i = 0; i < readers; i++) {
        reader_ids[i] = i;
        pthread_create(&readers_t[i], NULL, reader_func, &reader_ids[i]);
    }

    for (int i = 0; i < writers; i++) {
        writer_ids[i] = i;
        pthread_create(&writers_t[i], NULL, writer_func, &writer_ids[i]);
    }

    for (int i = 0; i < writers; i++)
        pthread_join(writers_t[i], NULL);

    for (int i = 0; i < readers; i++)
        pthread_join(readers_t[i], NULL);

    sem_destroy(&readAccess);
    sem_destroy(&bookAccess);

    printf("\nAll threads finished.\n");
    return 0;
}

void *reader_func(void *r) {
    int rNo = *((int *)r) + 1;
    printf("\nReader %d: wanting to read", rNo);
    sleep(rand() % sleepMod);

    if (isSync)
        sem_wait(&readAccess);
    else
        sched_yield();

    readCount++;
    if (readCount == 1)
        sem_wait(&bookAccess);

    if (isSync)
        sem_post(&readAccess);

    printf("\nReader %d: reading", rNo);
    sleep(rand() % sleepMod);

    if (isSync)
        sem_wait(&readAccess);

    readCount--;
    printf("\nReader %d: leaving reading", rNo);
    sleep(rand() % sleepMod);

    if (readCount == 0)
        sem_post(&bookAccess);

    if (isSync)
        sem_post(&readAccess);

    printf("\nReader %d: finished", rNo);
    sleep(rand() % sleepMod);

    pthread_exit(0);
}

void *writer_func(void *w) {
    int wNo = *((int *)w) + 1;
    printf("\nWriter %d: wanting to write", wNo);
    sleep(rand() % sleepMod);

    if (isSync)
        sem_wait(&bookAccess);
    else
        sched_yield();

    printf("\nWriter %d: writing", wNo);
    sleep(rand() % sleepMod);

    printf("\nWriter %d: leaving writing", wNo);
    sleep(rand() % sleepMod);

    if (isSync)
        sem_post(&bookAccess);

    printf("\nWriter %d: finished", wNo);
    sleep(rand() % sleepMod);

    pthread_exit(0);
}

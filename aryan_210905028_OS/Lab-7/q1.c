#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buf[5], f, r;
sem_t mutex, full, empty, atmost10;
int produced, consumed;

void *produce(void *arg)
{
    while (1)
    {
        sem_wait(atmost10);
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("produced item is %d\n", produced);
        buf[(++r) % 10] = produced;
        produced++;
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);
        if (produced - consumed <= 10)
        {
            sem_post(&atmost10);
        }
    }
}

void *consume(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buf[(++f) % 10];
        consumed++;
        printf("consumed item is %d\n", item);
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);
        if (produced - consumed <= 10)
        {
            sem_post(&atmost10);
        }
        sleep(1);
    }
}

void main()
{
    pthread_t tid1, tid2;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    sem_init(&atmost10, 0, 1);
    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consume, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
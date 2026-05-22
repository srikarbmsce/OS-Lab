#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t chopstick[N];
pthread_t philos[N];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is Thinking\n", id);
        sleep(1);

        sem_wait(&chopstick[id]);
        printf("Philosopher %d picked up Left Chopstick %d\n", id, id);

        sem_wait(&chopstick[(id + 1) % N]);
        printf("Philosopher %d picked up Right Chopstick %d\n",
               id, (id + 1) % N);

        printf("Philosopher %d is Eating\n", id);
        sleep(2);

        sem_post(&chopstick[(id + 1) % N]);
        sem_post(&chopstick[id]);

        printf("Philosopher %d finished Eating\n", id);
    }
}

int main()
{
    int i;
    int phil_num[N];
    for (i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }
    for (i = 0; i < N; i++)
    {
        phil_num[i] = i;
        pthread_create(&philos[i], NULL, philosopher, &phil_num[i]);
    }
    for (i = 0; i < N; i++)
    {
        pthread_join(philos[i], NULL);
    }
    for (i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }
    return 0;
}

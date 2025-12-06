#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "my_semaphore.h"

#define CYCLES 1000000

typedef struct {
    int id;
} philosophe_arg;

my_semaphore* forks;
int num_philosophers;

void* philosopher_thread(void* arg) {
    philosophe_arg *parg = (philosophe_arg*)arg;
    int id = parg->id;
    free(parg);

    for (int i = 0; i < CYCLES; ++i) {
        if (id % 2 == 0) {
            my_semaphore_wait(&forks[id]);
            my_semaphore_wait(&forks[(id + 1) % num_philosophers]);
        } else {
            my_semaphore_wait(&forks[(id + 1) % num_philosophers]);
            my_semaphore_wait(&forks[id]);
        }

        my_semaphore_post(&forks[id]);
        my_semaphore_post(&forks[(id + 1) % num_philosophers]);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s num_philosophers\n", argv[0]);
        return EXIT_FAILURE;
    }
    num_philosophers = atoi(argv[1]);
    if (num_philosophers <= 0) {
        fprintf(stderr, "Number of philosophers must be positive\n");
        return EXIT_FAILURE;
    }

    forks = malloc(num_philosophers * sizeof(my_semaphore));
    if (forks == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_philosophers; ++i) {
        my_semaphore_init(&forks[i], 1);
    }

    pthread_t *threads = malloc(num_philosophers * sizeof(pthread_t));
    if (threads == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_philosophers; ++i) {
        philosophe_arg *arg = malloc(sizeof(philosophe_arg));
        arg->id = i;
        if (pthread_create(&threads[i], NULL, philosopher_thread, arg) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < num_philosophers; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec)
                   + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%.6f\n", elapsed);

    free(forks);
    free(threads);
    return EXIT_SUCCESS;
}

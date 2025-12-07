#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <time.h>


#define CYCLES 1000000


pthread_mutex_t *forks;
int num_philosophers;


void* philosopher_thread(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < CYCLES; ++i) {
       
        if (id % 2 == 0) {

            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id + 1) % num_philosophers]);
        } else {
  
            pthread_mutex_lock(&forks[(id + 1) % num_philosophers]);
            pthread_mutex_lock(&forks[id]);
        }
        
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % num_philosophers]);
   
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


    forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    if (forks == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }


    pthread_t *threads = malloc(num_philosophers * sizeof(pthread_t));
    int *ids = malloc(num_philosophers * sizeof(int));
    if (threads == NULL || ids == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_philosophers; ++i) {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher_thread, &ids[i]) != 0) {
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


    for (int i = 0; i < num_philosophers; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }
    free(forks);
    free(threads);
    free(ids);

    return EXIT_SUCCESS;
}
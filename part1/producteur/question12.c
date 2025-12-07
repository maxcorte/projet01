#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NITEMS 131072
#define BUFFER_SIZE 8

int num_producers;
int num_consumers;

int buffer[BUFFER_SIZE];
int in_idx = 0;
int out_idx = 0;

pthread_mutex_t buffer_mutex;
sem_t empty_sem;
sem_t full_sem;

int items_per_producer;
int extra_producer_items;
int items_per_consumer;
int extra_consumer_items;

struct prod_arg {
    int id;
};

struct cons_arg {
    int id;
};

void* producer_thread(void* arg) {
    struct prod_arg *parg = (struct prod_arg*)arg;
    int id = parg->id;
    free(parg);

    int produce_count = items_per_producer + (id < extra_producer_items ? 1 : 0);

    for (int i = 0; i < produce_count; ++i) {
        // "Travail" hors section critique
        for (int k = 0; k < 10000; k++);

        sem_wait(&empty_sem);

        pthread_mutex_lock(&buffer_mutex);
        buffer[in_idx] = id;  // on écrit l'ID du producteur
        in_idx = (in_idx + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&full_sem);
    }
    return NULL;
}

void* consumer_thread(void* arg) {
    struct cons_arg *carg = (struct cons_arg*)arg;
    int id = carg->id;
    free(carg);

    int consume_count = items_per_consumer + (id < extra_consumer_items ? 1 : 0);

    for (int i = 0; i < consume_count; ++i) {
        // "Travail" hors section critique
        for (int k = 0; k < 10000; k++);

        sem_wait(&full_sem);

        pthread_mutex_lock(&buffer_mutex);
        int item = buffer[out_idx];
        (void)item; // éventuellement vérifier ou afficher
        out_idx = (out_idx + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&buffer_mutex);

        sem_post(&empty_sem);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s num_producers num_consumers\n", argv[0]);
        return EXIT_FAILURE;
    }

    num_producers = atoi(argv[1]);
    num_consumers = atoi(argv[2]);
    if (num_producers <= 0 || num_consumers <= 0) {
        fprintf(stderr, "Number of producers and consumers must be positive\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&buffer_mutex, NULL);
    sem_init(&empty_sem, 0, BUFFER_SIZE);
    sem_init(&full_sem, 0, 0);

    items_per_producer = NITEMS / num_producers;
    extra_producer_items = NITEMS % num_producers;
    items_per_consumer = NITEMS / num_consumers;
    extra_consumer_items = NITEMS % num_consumers;

    pthread_t *prod_threads = malloc(num_producers * sizeof(pthread_t));
    pthread_t *cons_threads = malloc(num_consumers * sizeof(pthread_t));
    if (prod_threads == NULL || cons_threads == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_producers; ++i) {
        struct prod_arg *arg = malloc(sizeof(struct prod_arg));
        arg->id = i;
        if (pthread_create(&prod_threads[i], NULL, producer_thread, arg) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int j = 0; j < num_consumers; ++j) {
        struct cons_arg *arg = malloc(sizeof(struct cons_arg));
        arg->id = j;
        if (pthread_create(&cons_threads[j], NULL, consumer_thread, arg) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < num_producers; ++i) {
        pthread_join(prod_threads[i], NULL);
    }
    for (int j = 0; j < num_consumers; ++j) {
        pthread_join(cons_threads[j], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec)
                   + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%.6f\n", elapsed);

    pthread_mutex_destroy(&buffer_mutex);
    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    free(prod_threads);
    free(cons_threads);

    return EXIT_SUCCESS;
}
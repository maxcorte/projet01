#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "my_semaphore.h"


#define NITEMS 131072



#define BUFFER_SIZE 8

int num_producers;
int num_consumers;


int buffer[BUFFER_SIZE];
int in_idx = 0;
int out_idx = 0;


my_semaphore buffer_mutex;
my_semaphore empty_sem;
my_semaphore full_sem;


int items_per_producer;
int extra_producer_items;
int items_per_consumer;
int extra_consumer_items;


void* producer_thread(void* arg) {
    int id = *(int*)arg;

    int produce_count = items_per_producer + (id < extra_producer_items ? 1 : 0);
    for (int i = 0; i < produce_count; ++i) {
    
        my_semaphore_wait(&empty_sem);
  
        my_semaphore_wait(&buffer_mutex);
     
        buffer[in_idx] = 1;
        in_idx = (in_idx + 1) % BUFFER_SIZE;
      
        my_semaphore_post(&buffer_mutex);
        my_semaphore_post(&full_sem);
    }
    return NULL;
}


void* consumer_thread(void* arg) {
    int id = *(int*)arg;

    int consume_count = items_per_consumer + (id < extra_consumer_items ? 1 : 0);
    for (int i = 0; i < consume_count; ++i) {

        my_semaphore_wait(&full_sem);
    
        my_semaphore_wait(&buffer_mutex);
        int item = buffer[out_idx];
        (void)item; 
        out_idx = (out_idx + 1) % BUFFER_SIZE;

        my_semaphore_post(&buffer_mutex);
        my_semaphore_post(&empty_sem);
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

 
    my_semaphore_init(&buffer_mutex, 1);
    my_semaphore_init(&empty_sem, BUFFER_SIZE);
    my_semaphore_init(&full_sem, 0);


    items_per_producer = NITEMS / num_producers;
    extra_producer_items = NITEMS % num_producers;
    items_per_consumer = NITEMS / num_consumers;
    extra_consumer_items = NITEMS % num_consumers;


    pthread_t *prod_threads = malloc(num_producers * sizeof(pthread_t));
    pthread_t *cons_threads = malloc(num_consumers * sizeof(pthread_t));
    int *prod_ids = malloc(num_producers * sizeof(int));
    int *cons_ids = malloc(num_consumers * sizeof(int));
    if (prod_threads == NULL || cons_threads == NULL || prod_ids == NULL || cons_ids == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_producers; ++i) {
        prod_ids[i] = i;
        if (pthread_create(&prod_threads[i], NULL, producer_thread, &prod_ids[i]) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int j = 0; j < num_consumers; ++j) {
        cons_ids[j] = j;
        if (pthread_create(&cons_threads[j], NULL, consumer_thread, &cons_ids[j]) != 0) {
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


    free(prod_threads);
    free(cons_threads);
    free(prod_ids);
    free(cons_ids);

    return EXIT_SUCCESS;
}
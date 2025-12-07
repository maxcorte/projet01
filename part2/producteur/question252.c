#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "my_semaphore.h"



#define TOTAL_ITEMS 32768    
#define BUFFER_SIZE 8

active_semaphore empty_sem;
active_semaphore full_sem;
spinlock_ttas buffer_lock;

int buffer[BUFFER_SIZE];
int in_idx = 0;
int out_idx = 0;

int num_producers = 0;
int num_consumers = 0;

void cpu_simulation(void) {
    for (int i = 0; i < 10000; i++);
}

void* producer(void* arg) {
    int id = *(int*)arg;
    int items_per_producer = TOTAL_ITEMS / num_producers;
    
    for (int i = 0; i < items_per_producer; i++) {
       
        active_semaphore_wait(&empty_sem);
        
      
        while (testAndSet((volatile int*)&buffer_lock.locked) != 0);
        buffer[in_idx] = id;
        in_idx = (in_idx + 1) % BUFFER_SIZE;
        buffer_lock.locked = 0;
     
        

        active_semaphore_post(&full_sem);
        

        cpu_simulation();
    }
    
    free(arg);
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    int items_per_consumer = TOTAL_ITEMS / num_consumers;
    
    for (int i = 0; i < items_per_consumer; i++) {

        active_semaphore_wait(&full_sem);
        

        while (testAndSet((volatile int*)&buffer_lock.locked) != 0);
        int item = buffer[out_idx];
        (void)item;
        out_idx = (out_idx + 1) % BUFFER_SIZE;
        buffer_lock.locked = 0;
    
        
 
        active_semaphore_post(&empty_sem);
        
        cpu_simulation();
    }
    
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_producers> <num_consumers>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    num_producers = atoi(argv[1]);
    num_consumers = atoi(argv[2]);
    
    if (num_producers <= 0 || num_consumers <= 0) {
        fprintf(stderr, "Nombre de producteurs et consommateurs doit être positif\n");
        return EXIT_FAILURE;
    }
    
    active_semaphore_init(&empty_sem, BUFFER_SIZE);
    active_semaphore_init(&full_sem, 0);
    spinlock_ttas_init(&buffer_lock);
    
    pthread_t *producers = malloc(num_producers * sizeof(pthread_t));
    pthread_t *consumers = malloc(num_consumers * sizeof(pthread_t));
    
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    for (int i = 0; i < num_producers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&producers[i], NULL, producer, id);
    }
    
    for (int i = 0; i < num_consumers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&consumers[i], NULL, consumer, id);
    }
    
    for (int i = 0; i < num_producers; i++)
        pthread_join(producers[i], NULL);
    for (int i = 0; i < num_consumers; i++)
        pthread_join(consumers[i], NULL);
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    
    printf("%.6f\n", elapsed);
    fflush(stdout);
    
    free(producers);
    free(consumers);
    
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "my_semaphore.h"

#define TOTAL_WRITES 6400
#define TOTAL_READS 25400

spinlock_ttas m_rcount_lock;
spinlock_ttas m_wcount_lock;
spinlock_ttas z_lock;
active_semaphore wsem_db;
active_semaphore rsem_db;

int rcount = 0;
int wcount = 0;
int num_readers = 0;
int num_writers = 0;

void cpu_simulation(void) {
    for (int i = 0; i < 10000; i++);
}

void* writer(void* arg) {
    int id = *(int*)arg;
    int writes_per_writer = TOTAL_WRITES / num_writers;
    
    for (int i = 0; i < writes_per_writer; i++) {

        while (testAndSet((volatile int*)&m_wcount_lock.locked) != 0);
        wcount++;
        if (wcount == 1) {
            active_semaphore_wait(&rsem_db);
        }
        m_wcount_lock.locked = 0;
        
        active_semaphore_wait(&wsem_db);
        
       
        cpu_simulation();
        
        active_semaphore_post(&wsem_db);
        
        while (testAndSet((volatile int*)&m_wcount_lock.locked) != 0);
        wcount--;
        if (wcount == 0) {
            active_semaphore_post(&rsem_db);
        }
        m_wcount_lock.locked = 0;
    }
    
    free(arg);
    return NULL;
}

void* reader(void* arg) {
    int id = *(int*)arg;
    int reads_per_reader = TOTAL_READS / num_readers;
    
    for (int i = 0; i < reads_per_reader; i++) {
        while (testAndSet((volatile int*)&z_lock.locked) != 0);
        active_semaphore_wait(&rsem_db);
        
        while (testAndSet((volatile int*)&m_rcount_lock.locked) != 0);
        rcount++;
        if (rcount == 1) {
            active_semaphore_wait(&wsem_db);
        }
        m_rcount_lock.locked = 0;
        
        active_semaphore_post(&rsem_db);
        z_lock.locked = 0;
       
        cpu_simulation();

        
        while (testAndSet((volatile int*)&m_rcount_lock.locked) != 0);
        rcount--;
        if (rcount == 0) {
            active_semaphore_post(&wsem_db);
        }
        m_rcount_lock.locked = 0;
    }
    
    free(arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_readers> <num_writers>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    num_readers = atoi(argv[1]);
    num_writers = atoi(argv[2]);
    
    if (num_readers <= 0 || num_writers <= 0) {
        fprintf(stderr, "Nombre de lecteurs et écrivains doit être positif\n");
        return EXIT_FAILURE;
    }
    
    spinlock_ttas_init(&m_rcount_lock);
    spinlock_ttas_init(&m_wcount_lock);
    spinlock_ttas_init(&z_lock);
    active_semaphore_init(&wsem_db, 1);
    active_semaphore_init(&rsem_db, 1);
    
    pthread_t *readers = malloc(num_readers * sizeof(pthread_t));
    pthread_t *writers = malloc(num_writers * sizeof(pthread_t));
    
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    for (int i = 0; i < num_readers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&readers[i], NULL, reader, id);
    }

    for (int i = 0; i < num_writers; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&writers[i], NULL, writer, id);
    }
    
    for (int i = 0; i < num_readers; i++)
        pthread_join(readers[i], NULL);
    for (int i = 0; i < num_writers; i++)
        pthread_join(writers[i], NULL);
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    
    printf("%.6f\n", elapsed);
    fflush(stdout);
    
    free(readers);
    free(writers);
    
    return EXIT_SUCCESS;
}

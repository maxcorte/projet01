#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "my_semaphore.h"


struct philosophe_arg {
    int id;
    int PHILOSOPHES;
    spinlock_ttas *baguette;  
};

void mange(int id) {


    for (int j = 0; j < 100; j++);
    
}

void* philosophe(void* arg) {
    struct philosophe_arg *args = (struct philosophe_arg*) arg;
    int id = args->id;
    int PHILOSOPHES = args->PHILOSOPHES;
    spinlock_ttas *baguette = args->baguette;  // ✅ Type changé
    
    int left;
    int right;
    
    if (id == 0) {
        left = id;
        right = PHILOSOPHES - 1;
    } else {
        left = id - 1;
        right = id;
    }
    
    int count = 0;
    while (count < 1000000) {
     
        spinlock_ttas_lock(&baguette[left]);
        spinlock_ttas_lock(&baguette[right]);
        
        mange(id);
        
 
        spinlock_ttas_unlock(&baguette[left]);
        spinlock_ttas_unlock(&baguette[right]);
        
        count++;
    }
    
    free(args);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_philosophers>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int PHILOSOPHES = atoi(argv[1]);
    
    if (PHILOSOPHES <= 0) {
        fprintf(stderr, "Number of philosophers must be positive\n");
        return EXIT_FAILURE;
    }
    
    pthread_t phil[PHILOSOPHES];
    spinlock_ttas baguette[PHILOSOPHES];  
    

    for (int i = 0; i < PHILOSOPHES; i++) {
        spinlock_ttas_init(&baguette[i]); 
    }
    
  
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    

    for (int i = 0; i < PHILOSOPHES; i++) {
        struct philosophe_arg *arg = malloc(sizeof(struct philosophe_arg));
        if (arg == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        
        arg->id = i;
        arg->PHILOSOPHES = PHILOSOPHES;
        arg->baguette = baguette;
        
        int err = pthread_create(&(phil[i]), NULL, &philosophe, arg);
        if (err != 0) {
            perror("pthread_create");
            free(arg);
            return EXIT_FAILURE;
        }
    }
    

    for (int i = PHILOSOPHES - 1; i >= 0; i--) {
        int err = pthread_join(phil[i], NULL);
        if (err != 0) {
            perror("pthread_join");
        }
    }
    

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed = (end_time.tv_sec - start_time.tv_sec) + 
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    

    printf("%.6f\n", elapsed);
    fflush(stdout);
    
    return EXIT_SUCCESS;
}

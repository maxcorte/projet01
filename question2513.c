#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_semaphore.h"


#define true 1
#define false 0

my_semaphore m_rcount;
my_semaphore m_wcount;
my_semaphore z;

my_semaphore wsem_db;
my_semaphore rsem_db;

int rcount = 0;
int wcount = 0;

void *writer(void *arg){
    int nb_ecritures = *(int*)arg;
    for(int i = 0; i < nb_ecritures; i++) {
        my_semaphore_wait(&m_wcount);
        wcount++;
        if(wcount == 1){
            my_semaphore_wait(&rsem_db);
        }
        my_semaphore_post(&m_wcount);

        my_semaphore_wait(&wsem_db);

        for(int i = 0; i<10000; i++); // Correspond au temps d'écriture d'un écrivain
        my_semaphore_post(&wsem_db);

        my_semaphore_wait(&m_wcount);
        wcount--;
        if(wcount == 0){
            my_semaphore_post(&rsem_db);
        }
        my_semaphore_post(&m_wcount);
    }

    return NULL;    
}

void *reader(void *arg){
    int nb_lectures = *(int*) arg;
    for(int i=0; i < nb_lectures; i++){
        my_semaphore_wait(&z);
        my_semaphore_wait(&rsem_db);

        my_semaphore_wait(&m_rcount);
        rcount++;
        if(rcount == 1){
            my_semaphore_wait(&wsem_db);
            //printf("First reader\n");
        }
        my_semaphore_post(&m_rcount);

        my_semaphore_post(&rsem_db);
        my_semaphore_post(&z);

        //printf("Reading\n")
        for(int i = 0; i<10000; i++); //Le temps pour la lecture

        my_semaphore_wait(&m_rcount);
        rcount--;
        if(rcount == 0){
            my_semaphore_post(&wsem_db);
            //printf("Last reader\n")
        }
        my_semaphore_post(&m_rcount);
    }

    return NULL;
}




int main(int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "Usage: %s <nombre_lecteurs> <nombre_ecrivains>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int num_reader = atoi(argv[1]);
    int num_writer = atoi(argv[2]);

    if (num_reader < 0 || num_writer < 0) {
        fprintf(stderr, "Number of readers and writers must be positive\n");
        return EXIT_FAILURE;
    }

    my_semaphore_init(&m_rcount, 1);
    my_semaphore_init(&m_wcount, 1);
    my_semaphore_init(&z, 1);

    my_semaphore_init(&wsem_db, 1);
    my_semaphore_init(&rsem_db, 1);

    
    int nb_ecritures = 6400;
    int nb_lectures = 25400/num_reader;
    pthread_t *threads = malloc((num_reader + num_writer) * sizeof(pthread_t));
    int *ecriture_id = malloc(num_writer * sizeof(int));
    int *lecture_id = malloc(num_reader * sizeof(int));

    if (threads == NULL || ecriture_id == NULL || lecture_id == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }


    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);


    // création des threads des lecteurs
    for(int i=0; i<num_reader; i++){
        lecture_id[i] = nb_lectures;
        pthread_create(&threads[i], NULL, reader, &lecture_id[i]);
    }

    // création des threads des écrivains
    for(int j=0; j < num_writer; j++){
        ecriture_id[j] = nb_ecritures;
        pthread_create(&threads[num_reader + j], NULL, writer, &ecriture_id[j]);
    }

    // On attend que tous les threads ait été créés
    for(int i = 0; i < (num_reader + num_writer); i++){
        pthread_join(threads[i], NULL);
    }


    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed = (end_time.tv_sec - start_time.tv_sec)
                   + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("%.6f\n", elapsed);

    free(threads);
    free(lecture_id);
    free(ecriture_id);
}
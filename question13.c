#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define true 1
#define false 0

pthread_mutex_t m_rcount;
pthread_mutex_t m_wcount;
pthread_mutex_t z;

sem_t wsem_db;
sem_t rsem_db;

int rcount = 0;
int wcount = 0;

void *writer(void *arg){
    int nb_ecritures = *(int*)arg;
    for(int i = 0; i < nb_ecritures; i++) {
        pthread_mutex_lock(&m_wcount);
        wcount++;
        if(wcount == 1){
            sem_wait(&rsem_db);
        }
        pthread_mutex_unlock(&m_wcount);

        sem_wait(&wsem_db);

        for(int i = 0; i<10000; i++); // Correspond au temps d'écriture d'un écrivain
        sem_post(&wsem_db);

        pthread_mutex_lock(&m_wcount);
        wcount--;
        if(wcount == 0){
            sem_post(&rsem_db);
        }
        pthread_mutex_unlock(&m_wcount);
    }

    return NULL;    
}

void *reader(void *arg){
    int nb_lectures = *(int*) arg;
    for(int i=0; i < nb_lectures; i++){
        pthread_mutex_lock(&z);
        sem_wait(&rsem_db);

        pthread_mutex_lock(&m_rcount);
        rcount++;
        if(rcount == 1){
            sem_wait(&wsem_db);
            //printf("First reader\n");
        }
        pthread_mutex_unlock(&m_rcount);

        sem_post(&rsem_db);
        pthread_mutex_unlock(&z);

        //printf("Reading\n")
        for(int i = 0; i<10000; i++); //Le temps pour la lecture

        pthread_mutex_lock(&m_rcount);
        rcount--;
        if(rcount == 0){
            sem_post(&wsem_db);
            //printf("Last reader\n")
        }
        pthread_mutex_unlock(&m_rcount);
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

    pthread_mutex_init(&m_rcount, NULL);
    pthread_mutex_init(&m_wcount, NULL);
    pthread_mutex_init(&z, NULL);

    sem_init(&wsem_db, 0, 1);
    sem_init(&rsem_db, 0, 1);

    
    int nb_ecritures = 6400/num_writer;
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


    pthread_mutex_destroy(&m_rcount);
    pthread_mutex_destroy(&m_wcount);
    pthread_mutex_destroy(&z);

    sem_destroy(&rsem_db);
    sem_destroy(&wsem_db);

    free(threads);
    free(lecture_id);
    free(ecriture_id);
}
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t m_rcount;
pthread_mutex_t m_wcount;
pthread_mutex_t z;

sem_t wsem_db;
sem_t rsem_db;

int rcount = 0;
int wcount = 0;

struct writer_arg {
    int writes;
};

struct reader_arg {
    int reads;
};

void *writer(void *arg){
    struct writer_arg *warg = (struct writer_arg*)arg;
    int nb_ecritures = warg->writes;
    free(warg);

    for(int i = 0; i < nb_ecritures; i++) {
        pthread_mutex_lock(&m_wcount);
        wcount++;
        if (wcount == 1) {
            sem_wait(&rsem_db);
        }
        pthread_mutex_unlock(&m_wcount);

        sem_wait(&wsem_db);

        // écriture DANS la zone critique
        for (int k = 0; k < 10000; k++);

        sem_post(&wsem_db);

        pthread_mutex_lock(&m_wcount);
        wcount--;
        if (wcount == 0) {
            sem_post(&rsem_db);
        }
        pthread_mutex_unlock(&m_wcount);
    }

    return NULL;
}

void *reader(void *arg){
    struct reader_arg *rarg = (struct reader_arg*)arg;
    int nb_lectures = rarg->reads;
    free(rarg);

    for (int i = 0; i < nb_lectures; i++) {
        pthread_mutex_lock(&z);
        sem_wait(&rsem_db);

        pthread_mutex_lock(&m_rcount);
        rcount++;
        if (rcount == 1) {
            sem_wait(&wsem_db);
        }
        pthread_mutex_unlock(&m_rcount);

        sem_post(&rsem_db);
        pthread_mutex_unlock(&z);

        // lecture DANS la zone critique
        for (int k = 0; k < 10000; k++);

        pthread_mutex_lock(&m_rcount);
        rcount--;
        if (rcount == 0) {
            sem_post(&wsem_db);
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

    if (num_reader <= 0 || num_writer <= 0) {
        fprintf(stderr, "Number of readers and writers must be positive\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_init(&m_rcount, NULL);
    pthread_mutex_init(&m_wcount, NULL);
    pthread_mutex_init(&z, NULL);

    sem_init(&wsem_db, 0, 1);
    sem_init(&rsem_db, 0, 1);

    // Répartition exacte des 6400 / 25400
    int base_writes = 6400 / num_writer;
    int extra_writes = 6400 % num_writer;
    int base_reads  = 25400 / num_reader;
    int extra_reads = 25400 % num_reader;

    pthread_t *threads = malloc((num_reader + num_writer) * sizeof(pthread_t));
    if (threads == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // création des threads lecteurs
    for (int i = 0; i < num_reader; i++) {
        struct reader_arg *arg = malloc(sizeof(struct reader_arg));
        arg->reads = base_reads + (i < extra_reads ? 1 : 0);
        if (pthread_create(&threads[i], NULL, reader, arg) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    // création des threads écrivains
    for (int j = 0; j < num_writer; j++) {
        struct writer_arg *arg = malloc(sizeof(struct writer_arg));
        arg->writes = base_writes + (j < extra_writes ? 1 : 0);
        if (pthread_create(&threads[num_reader + j], NULL, writer, arg) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < (num_reader + num_writer); i++) {
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
    return EXIT_SUCCESS;
}

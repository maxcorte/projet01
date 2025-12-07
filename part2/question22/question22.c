#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



//###################################
//### Reprise du code question 21 ###
//###################################

volatile int lock_var; 

void lock(volatile int *lock_var){
    int old; 
    do { // On crée la boucle qui va s'exécuter tant que la valeur de old est 1.
        __asm__ volatile ( // Définition de l'assembleur inline
            "xchg %0, %1"
            : "=r" (old), "=m" (*lock_var)
            : "0" (1), "m" (*lock_var)
        );
    } while (old == 1);
}



// Les variables après le premier : sont les variables que l'on va modifier (les sorties), 
// Celles après les : sont celles que l'on utilise (les entrées)

// Le =r veut dire que l'on stoque dans un registre la variable old après l'exécution (car elle est à la ligne de sortie)
// le =m veut dire que l'on retourne l'accès mémoire de lock_var

// "0" (1) dit : “prend la valeur 1, et place-la dans le même registre que l’argument de sortie numéro 0.” ici c'est old


void unlock(volatile int *lock_var){
    *lock_var = 0;
}

//##########################################################

void* thread_critical(void* arg){
    int nb_critical_section = *(int*)arg;
    for(int i=0; i < nb_critical_section; i++){
        lock(&lock_var);
        for (int j=0; j<10000; j++);
        unlock(&lock_var);
    }
    return NULL;
}


int main (int argc, char* argv[]){
    // Erreur dans le cas ou il n'y a pas, ou pas assez d'arguments.

    if (argc != 2){
        fprintf(stderr, "You need to have only 1 argument: N, the number of threads\n");
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]);
    int nbCriticalSection = 32768/N;

    lock_var = 0;

    pthread_t *threads = malloc(N * sizeof(pthread_t));

    // Vérification que les threads se soient bien créés.
    // Pas besoin d'id car tous les threads font la meme chose et n'ont pas besoin de se rappeler leur 
    // fonction ou leur position

    if (threads == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }


    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);


    for(int i=0; i < N; i++){
        if (pthread_create(&threads[i], NULL, thread_critical, &nbCriticalSection) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < N; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed = (end_time.tv_sec - start_time.tv_sec)
                   + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("%.6f\n", elapsed);
    
    free(threads);

    return EXIT_SUCCESS;
}
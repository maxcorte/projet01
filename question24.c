#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_semaphore.h"

static inline int testAndSet(volatile int *lock_var){
    int old; 
    __asm__ volatile ( // Définition de l'assembleur inline
            "xchg %0, %1"
            : "=r" (old), "=m" (*lock_var)
            : "0" (1), "m" (*lock_var)
    );
    return old;
}


void unlock(volatile int *lock_var){
    *lock_var = 0;
}


void lock(volatile int *lock_var){
    for(;;){
        while(*lock_var != 0){}
        if(testAndSet(lock_var) == 0){
            return;
        }
    }
}

void my_semaphore_init(my_semaphore *semaphore, int initial_value){
    semaphore->value = initial_value;
    semaphore->lock_var = 0;
}


void my_semaphore_wait(my_semaphore *semaphore){
    for(;;){
        lock(&semaphore->lock_var);
        if(semaphore->value > 0){
            semaphore->value--; //Il y a plusieurs ressources disponibles, donc on en prend une. 
            unlock(&semaphore->lock_var);
            return;
        }
        // Sinon on doit attendre tant qu'une valeur n'est pas rajoutée
        unlock(&semaphore->lock_var);
    }
}

void my_semaphore_post(my_semaphore *semaphore){
    lock(&semaphore->lock_var);
    semaphore->value ++; //On libère une ressource
    unlock(&semaphore->lock_var);
}
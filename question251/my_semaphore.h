#ifndef MY_SEMAPHORE_H
#define MY_SEMAPHORE_H

typedef struct {
    volatile int value; // number of available ressources
    volatile int lock_var;
} my_semaphore;


void unlock(volatile int *lock_var);
void lock(volatile int *lock_var);

void my_semaphore_init(my_semaphore *semaphore, int initial_value);
void my_semaphore_wait(my_semaphore *semaphore);
void my_semaphore_post(my_semaphore *semaphore);

#endif
#ifndef SPINLOCK_H
#define SPINLOCK_H



typedef struct {
    volatile int locked; 
} spinlock_tas;


static inline int testAndSet(volatile int *lock_var) {
    int old;
    
    __asm__ volatile (
        "xchg %0, %1"
        : "=r" (old), "=m" (*lock_var)
        : "0" (1), "m" (*lock_var)
    );
    
    return old;
}


void spinlock_tas_init(spinlock_tas *lock) {
    lock->locked = 0;
}

void spinlock_tas_lock(spinlock_tas *lock) {

    while (testAndSet((volatile int*)&lock->locked) != 0) {
      
    }
 
}

void spinlock_tas_unlock(spinlock_tas *lock) {
    lock->locked = 0;
}

typedef struct {
    volatile int locked;
} spinlock_ttas;

void spinlock_ttas_init(spinlock_ttas *lock) {
    lock->locked = 0;
}

void spinlock_ttas_lock(spinlock_ttas *lock) {

    while (1) {
        while (lock->locked != 0) {
         
        }
        
        if (testAndSet((volatile int*)&lock->locked) == 0) {
            break;
        }
    }
}

void spinlock_ttas_unlock(spinlock_ttas *lock) {
    lock->locked = 0;
}

typedef struct {
    volatile int value;        
    volatile int lock_spinlock;  
} active_semaphore;

void active_semaphore_init(active_semaphore *sem, int initial_value) {
    sem->value = initial_value;
    sem->lock_spinlock = 0;
}

void active_semaphore_wait(active_semaphore *sem) {
    while (1) {
        while (testAndSet((volatile int*)&sem->lock_spinlock) != 0) {
        }
        
        if (sem->value > 0) {
            sem->value--;
            sem->lock_spinlock = 0;
            return;  
        }
        sem->lock_spinlock = 0;
    }
}

void active_semaphore_post(active_semaphore *sem) {
    while (testAndSet((volatile int*)&sem->lock_spinlock) != 0) {
    }
    
    sem->value++;
    sem->lock_spinlock = 0;
}

#endif
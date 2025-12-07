volatile int lock_var = 0; 

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


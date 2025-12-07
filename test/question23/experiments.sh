#!/bin/bash

# Exécutions avec 2, 4, 8, 16, 32 threads, 5 essais chacun
for N in 2 4 8 16 32
do
    echo "Threads = $N"
    for i in {1..5}
    do
        ./question23 "$N"
    done
    echo ""
done

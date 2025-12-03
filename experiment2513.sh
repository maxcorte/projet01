#!/usr/bin/env bash
# experiment lecteurs ecrivains attente active

program="question2513.c"

threads=(1 2 4 8 16 32)
measures=5

for thread_numbers in "${threads[@]}"; do
    thread=$((thread_numbers))
    for ((i=1; i<=measures; i++)); do
        start=$(date +%s.%N)
        $prog "$thread" > /dev/null 2>&1
        end=$(date +%s.%N)
        elapsed_time=$(echo "$end - $start" | bc)
        echo "$thread_numbers,$i,$elapsed_time"
    done
done
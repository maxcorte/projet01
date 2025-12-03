#!/usr/bin/env bash
# experiment philosophes attente active

program="question2511.c"

threads=(1 2 4 8 16 32)
measures=5

for thread_numbers in "${threads[@]}"; do
    thread1=$((thread_numbers/2))
    thread2=$((thread_numbers/2))
    for ((i=1; i<=measures; i++)); do
        start=$(date +%s.%N)
        $prog "$thread1" "$thread2" > /dev/null 2>&1
        end=$(date +%s.%N)
        elapsed_time=$(echo "$end - $start" | bc)
        echo "$thread_numbers,$i,$elapsed_time"
    done
done


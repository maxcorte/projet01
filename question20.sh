#!/usr/bin/env bash

programs=("./question21" "./question22" "./question23" "./question2511" "./question2512" "./question2513")

threads=(1 2 4 8 16 32)
measures=5

for prog in "${programs[@]}"; do
    csv_file="${prog##./}_performance.csv"
    echo "thread_total,run_index,total_time_seconds" > "$csv_file"
    for thread_numbers in "${threads[@]}"; do
        for ((i=1; i<=measures; i++)); do
            start=$(date +%s.%N)
            $prog "$thread_numbers" > /dev/null 2>&1
            end=$(date +%s.%N)
            elapsed_time=$(echo "$end - $start" | bc)
            echo "$thread_numbers,$i,$elapsed_time" >> "$csv_file"
        done
    done
done

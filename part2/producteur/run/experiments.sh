#!/bin/bash

filename="./question252"
echo "Time for $filename - Producteurs-Consommateurs (Spin-Locks)"
echo "run_1, run_2, run_3, run_4, run_5"

if [ ! -f "$filename" ]; then
    echo "ERROR: $filename not found. Please compile first."
    exit 1
fi

for (( i=2; i<=32; i*=2 ))
do
    producers=$((i / 2))
    consumers=$((i - producers))
    
    if [ "$producers" -le 0 ]; then
        producers=1
    fi
    if [ "$consumers" -le 0 ]; then
        consumers=1
    fi
    
    for ((k=0; k<5; k++))
    do      
        elapsed=$($filename "$producers" "$consumers" 2>/dev/null)
        
        if [ $? -eq 0 ]; then
            echo -n "$elapsed"
        else
            echo -n "ERROR"
        fi
        
        if [ $k -ne 4 ]; then
            echo -n ","
        fi
    done
    
    printf "\n"
done

printf "\n"
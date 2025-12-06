#!/bin/bash

filename="./question251"
echo "Time for $filename-Part1"
echo "run_1, run_2, run_3, run_4, run_5"

for (( i=2; i<=32; i*=2))
do
    for((k=0; k<5; k++))
    do      
        # ✅ UN SEUL argument
        time=$(/usr/bin/time -o /tmp/mesure -f "%e" ./$filename $i)
        cat /tmp/mesure | tr -d "\n"
        if [ $k -ne 4 ]; then
            echo -n ","
        fi
    done
    printf "\n"
done
printf "\n"



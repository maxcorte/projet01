#!/bin/bash

filename="./question12"
echo "Time for $filename - Producers/Consumers"
echo "run_1,run_2,run_3,run_4,run_5"

for (( n=2; n<=32; n*=2 ))
do
    for (( k=0; k<5; k++ ))
    do
        /usr/bin/time -o /tmp/mesure -f "%e" "$filename" "$n" "$n" >/dev/null 2>&1
        cat /tmp/mesure | tr -d "\n"
        if [ $k -ne 4 ]; then
            echo -n ","
        fi
    done
    # ligne avec P,C au début
    sed -i "" "1s/^/${n},${n},/" /tmp/mesure 2>/dev/null || true
    echo    # saut de ligne
done

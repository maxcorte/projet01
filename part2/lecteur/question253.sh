#!/bin/bash



filename="./question253"
echo "Time for $filename - Lecteurs-Écrivains (Spin-Locks)"
echo "run_1, run_2, run_3, run_4, run_5"

if [ ! -f "$filename" ]; then
    echo "ERROR: $filename not found."
    exit 1
fi

for (( i=2; i<=32; i*=2 ))
do

    readers=$((i / 2))
    writers=$((i - readers))
    
    if [ "$readers" -le 0 ]; then
        readers=1
    fi
    if [ "$writers" -le 0 ]; then
        writers=1
    fi
    
    for ((k=0; k<5; k++))
    do      
 
        elapsed=$($filename "$readers" "$writers" 2>/dev/null)
        
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


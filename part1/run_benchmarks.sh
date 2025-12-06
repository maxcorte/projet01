#!/bin/bash


threads_list="2 4 8 16 32"


philo_csv="result_philo.csv"
prodcons_csv="result_prodcons.csv"



> "$philo_csv"
> "$prodcons_csv"



for th in $threads_list; do
    t1=$(./philosophes "$th")
    t2=$(./philosophes "$th")
    t3=$(./philosophes "$th")
    t4=$(./philosophes "$th")
    t5=$(./philosophes "$th")
    echo "$th,$t1,$t2,$t3,$t4,$t5" >> "$philo_csv"
done


for th in $threads_list; do
    t1=$(./prod_cons "$th" "$th")
    t2=$(./prod_cons "$th" "$th")
    t3=$(./prod_cons "$th" "$th")
    t4=$(./prod_cons "$th" "$th")
    t5=$(./prod_cons "$th" "$th")
    echo "$th,$t1,$t2,$t3,$t4,$t5" >> "$prodcons_csv"
done



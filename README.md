# projet01

Le projet 1 du cours *LINFO1252 - Systèmes informatiques* vise à nous faire comprendre l'utilité et l'importance de l'utilisation de plusieurs *threads*

La section 1 de ce projet nous permet de visualiser et mettre en oeuvre les outils de synchronisations vus en cours ainsi que durant les séances d'exercices. Nous y avons codé en C les trois problèmes suivants: 
* Le problème des philosophes
* Le problème des producteurs-consommateurs
* Le problème des lecteurs-écrivains

Ces trois fichiers peuvent être endus exécutables grâce au **Makefile**, plus précisément avec la ligne de commande:
`make`

Ensuite nous avons créé un fichier bash afin de réaliser le nombre de mesures pour chaque nombre de threads demandé (2, 4, 8, 16 et 32). Ce fichier peut être exécuté une fois les 3 problèmes rendus exécutables grâce à la ligne de commande suivante: 
`make bash`

Enfin, nous avons représenté sur différents graphes les performances réalisées afin de voir les évolutions des temps d'exécution en fonction du nombre de threads utilisés. Ces grphes sont générés avec la ligne de commade 
`make python`
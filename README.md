# projet01

Le projet 1 du cours *LINFO1252 - Systèmes informatiques* vise à nous faire comprendre l'utilité et l'importance de l'utilisation de plusieurs *threads*

La section 1 de ce projet nous permet de visualiser et mettre en oeuvre les outils de synchronisations vus en cours ainsi que durant les séances d'exercices. Nous y avons codé en C les trois problèmes suivants: 
* Le problème des philosophes
* Le problème des producteurs-consommateurs
* Le problème des lecteurs-écrivains

Le dossier est structuré de la manière suivante. Un dossier a été créé par partie (part1 et part2). A l'intérieur de ces deux dossiers, des sous-dossiers sont présents avec chacun le nom du problème qu'ils résolvent. Dans chacun de ces sous-dossiers nous avons:
* un fichier bash, 
* le code en c, 
* le fihcier csv obtenu sur le serveur, 
* le code python
* le pdf du graphe

Pour les dossiers de la partie 2, nous avons du créer une classe appelée **my_semaphore.h**. Ce fichier est donc présent en plus des 5 autres fichiers par dossier.

Dans le dossier principal, nous avons enfin les codes pythons qui permettent d'afficher les deux courbes par problème afin de pouvoir faire une comparaison sur le même graphe. 

Le **Makefile** permet de lancer tous les codes l'un à la suite de l'autre, plus précisément avec la ligne de commande:
`make`

Ensuite la commande `make bash` permet d'exécuter les fichiers bash qui sont dans chaque sous dossier, ce qui print dans le terminal les temps d'exécution. Nous ne les sauvegardons pas car nous avons les ficheirs CSV du sreveur qui sont sauvegardés dans les dossiers respectifs.

Enfin, nous avons représenté sur différents graphes les performances réalisées afin de voir les évolutions des temps d'exécution en fonction du nombre de threads utilisés. Ces graphes sont générés avec la ligne de commade 
`make python`

Ci dessous voici l'arbre de notre projet. 

```
./
├── part1/
│   ├── lecteur/
│   │   ├── plot_question3_POSIX.pdf
│   │   ├── question13.c
│   │   ├── question3.csv
│   │   ├── question3.py
│   │   └── question3.sh*
│   ├── philosophes/
│   │   ├── plot_question1_POSIX.pdf
│   │   ├── question11.c
│   │   ├── question1.csv
│   │   ├── question1.py
│   │   └── question1.sh*
│   └── producteur/
│       ├── plot_question2_POSIX.pdf
│       ├── question12.c
│       ├── question2.csv
│       ├── question2.py
│       └── question2.sh*
├── part2/
│   ├── lecteur/
│   │   ├── my_semaphore.h
│   │   ├── plot_question3_partie2.pdf
│   │   ├── question253.c
│   │   ├── question253.csv
│   │   ├── question253.py
│   │   └── question253.sh*
│   ├── philosophe/
│   │   ├── my_semaphore.h
│   │   ├── plot_question1_attente_active.pdf
│   │   ├── question251.c
│   │   ├── question251.csv
│   │   ├── question251.py
│   │   └── question251.sh*
│   ├── producteur/
│   │   ├── my_semaphore.h
│   │   ├── plot_question2_attente_active.pdf
│   │   ├── question252.c
│   │   ├── question252.csv
│   │   ├── question252.py
│   │   └── question252.sh*
│   ├── question22/
│   │   ├── question22.c
│   │   ├── question22.csv
│   │   ├── question22.pdf
│   │   ├── question22.py
│   │   └── question22.sh*
│   ├── question23/
│   │   ├── question23.c
│   │   ├── question23.csv
│   │   ├── question23.pdf
│   │   ├── question23.py
│   │   └── question23.sh*
│   ├── my_semaphore.h
│   └── question21.c
├── graphe_lect_ecr_global.pdf
├── graphe_philosophes_global.pdf
├── graphe_prod_cons_global.pdf
├── graphesalgorithmeGlobal.py
├── graphesLecteursEcrivainsGlobal.py
├── graphesPhilosophesGlobal.py
├── graphesProducteursConsommateursGlobal.py
├── grapheTAS_TATAS.pdf
├── Makefile
└── README.md
```
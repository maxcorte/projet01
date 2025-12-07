CC = gcc
CFLAGS = -Wall -Wextra -pthread
C_BINS = question11 question12 question13 question22 question23 question251 question252 question253
LIBS = -lpthread

.PHONY: all clean bash python

all: $(C_BINS)

question11: part1/philosophes/question11.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question12: part1/producteur/question12.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	
question13: part1/lecteur/question13.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question22: part2/question22/question22.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question23: part2/question23/question23.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question251: part2/philosophe/question251.c part2/philosophe/my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question252: part2/producteur/question252.c part2/producteur/my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question253: part2/lecteur/question253.c part2/lecteur/my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)




bash:
	chmod +x ./part1/philosophes/question1.sh
	./part1/philosophes/question1.sh
	chmod +x ./part1/producteur/question2.sh
	./part1/producteur/question2.sh
	chmod +x part1/lecteur/question3.sh
	./part1/lecteur/question3.sh
	chmod +x part2/question22/question22.sh
	./part2/question22/question22.sh
	chmod +x part2/question23/question23.sh
	./part2/question23/question23.sh
	chmod +x part2/philosophe/question251.sh
	./part2/philosophe/question251.sh
	chmod +x part2/producteur/question252.sh
	./part2/producteur/question252.sh
	chmod +x part2/lecteur/question253.sh
	./part2/lecteur/question253.sh
	

run: all
	./part1/philosophes/question11
	./part1/producteur/question12
	./part1/lecteur/question13
	./part2/question22/question22
	./part2/question23/question23
	./part2/philosophe/question251
	./part2/producteur/question252
	./part2/lecteur/question253


python:
	python3 part1/philosophes/question1.py
	python3 part1/producteur/question2.py
	python3 part1/lecteur/question3.py
	python3 part2/philosophe/question251.py
	python3 part2/producteur/question252.py
	python3 part2/lecteur/question253.py
	python3 graphesLecteursEcrivainsGlobal.py
	python3 graphesPhilosophesGlobal.py
	python3 graphesProducteursConsommateursGlobal.py
	python3 graphesalgorithmeGlobal.py

	
clean:
	rm -f $(C_BINS)
	rm -f ./plot_question1_POSIX.pdf ./plot_question2_POSIX.pdf ./plot_question3_POSIX.pdf
	rm -f ./plot_philosophe_partie2.pdf ./plot_producteur_partie2.pdf ./plot_lecteur_partie2.pdf
	rm -f ./question22.pdf ./question23.pdf
	rm -f ./graphe_lect_ecr_global.pdf ./graphe_philosophes_global.pdf ./graphe_prod_cons_global.pdf ./grapheTAS_TATAS.pdf

.DEFAULT_GOAL := all

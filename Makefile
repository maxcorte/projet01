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

question22: projet01/part2/question22/question22.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question23: projet01/part2/question23/question23.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question251: part2/philosophe/question251.c my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question252: part2/producteur/question252.c my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

question253: part2/lecteur/question253.c my_semaphore.h
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)




bash:
	chmod +x part1/philosophes/question1.sh
	./question1.sh
	chmod +x part1/producteur/question2.sh
	./question2.sh
	chmod +x part1/lecteur/question3.sh
	./question3.sh
	chmod +x projet01/part2/question22/question22.sh
	./question22.sh
	chmod +x projet01/part2/question23/question23.sh
	./question23.sh
	chmod +x part2/philosophe/question251.sh
	./question251.sh
	chmod +x part2/producteur/question252.sh
	./question252.sh
	chmod +x part2/lecteur/question253.sh
	./question253.sh
	

run: all
	./question11
	./question12
	./question13
	./question22
	./question23
	./question251
	./question252
	./question253


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

	
clean:
	rm -f $(C_BINS)
	rm -f ./question11_performance.csv ./question12_performance.csv ./question13_performance.csv
	rm -f ./question21_performance.csv ./question22_performance.csv ./question23_performance.csv ./question24_performance.csv
	rm -f ./question2511_performance.csv ./question2512_performance.csv ./question2513_performance.csv
	rm -f ./question11.pdf ./question12.pdf ./question13.pdf
	rm -f ./question21.pdf ./question22.pdf ./question23.pdf ./PlotQuestion_22_23.pdf
	rm -f ./GlobalPlotQuestion0.pdf ./GlobalPlotQuestion1.pdf ./GlobalPlotQuestion2.pdf

.DEFAULT_GOAL := all

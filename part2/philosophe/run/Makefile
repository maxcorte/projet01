CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBS = -lpthread

C_BINS = question251

.PHONY: all clean bash run

all: $(C_BINS)

question251: question251.c  my_semaphore.h
	$(CC) $(CFLAGS) question251.c  -o question251 $(LIBS)

bash: all
	chmod +x experiments.sh
	./experiments.sh

run: all
	./question251

clean:
	rm -f $(C_BINS) /tmp/mesure

.DEFAULT_GOAL := all

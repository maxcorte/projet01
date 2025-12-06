CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBS = -lpthread

C_BINS = question252

.PHONY: all clean bash run

all: $(C_BINS)

question252: question252.c  my_semaphore.h
	$(CC) $(CFLAGS) question252.c  -o question252 $(LIBS)

bash: all
	chmod +x experiments.sh
	./experiments.sh

run: all
	./question252

clean:
	rm -f $(C_BINS) /tmp/mesure

.DEFAULT_GOAL := all

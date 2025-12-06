CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBS = -lpthread

C_BINS = question253

.PHONY: all clean bash run

all: $(C_BINS)

question253: question253.c  my_semaphore.h
	$(CC) $(CFLAGS) question253.c  -o question253 $(LIBS)

bash: all
	chmod +x experiments.sh
	./experiments.sh

run: all
	./question253

clean:
	rm -f $(C_BINS) /tmp/mesure

.DEFAULT_GOAL := all

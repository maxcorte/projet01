CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBS = -lpthread

C_BINS = question23

.PHONY: all clean bash run

all: $(C_BINS)

question23: question23.c
	$(CC) $(CFLAGS) question23.c  -o question23 $(LIBS)

bash: all
	chmod +x experiments.sh
	./experiments.sh

run: all
	./question22

clean:
	rm -f $(C_BINS) /tmp/mesure

.DEFAULT_GOAL := all

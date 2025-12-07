CC = gcc
CFLAGS = -Wall -Wextra -pthread
LIBS = -lpthread

C_BINS = question22

.PHONY: all clean bash run

all: $(C_BINS)

question22: question22.c
	$(CC) $(CFLAGS) question22.c  -o question22 $(LIBS)

bash: all
	chmod +x experiments.sh
	./experiments.sh

run: all
	./question22

clean:
	rm -f $(C_BINS) /tmp/mesure

.DEFAULT_GOAL := all

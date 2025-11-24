CC = gcc
CFLAGS = -Wall -Wextra
C_SRCS = question11.c question12.c question13.c
C_BINS = question11 question12 question13

.PHONY: all clean bash python

all: $(C_BINS)

question11: question11.c
	$(CC) $(CFLAGS) $< -o $@

question12: question12.c
	$(CC) $(CFLAGS) $< -o $@
	
question13: question13.c
	$(CC) $(CFLAGS) $< -o $@
	
bash:
	chmod +x question14.sh
	./question14.sh
python:
	python3 question15.py

clean:
	rm -f $(C_BINS)

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

question21: question21.c
	$(CC) $(CFLAGS) $< -o $@

question22: question22.c
	$(CC) $(CFLAGS) $< -o $@

question23: question23.c
	$(CC) $(CFLAGS) $< -o $@
	
bash:
	chmod +x question14.sh
	./question14.sh
	chmod +x question20.sh
	./question20.sh
python:
	python3 question15.py
	python3 question20.py
	
clean:
	rm -f $(C_BINS)

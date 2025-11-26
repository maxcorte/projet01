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

question24: question24.c
	$(CC) $(CFLAGS) $< -o $@

question2511: question2511.c
	$(CC) $(CFLAGS) $< -o $@

question2512: question2512.c
	$(CC) $(CFLAGS) $< -o $@

question2513: question2513.c
	$(CC) $(CFLAGS) $< -o $@



bash:
	chmod +x question14.sh
	./question14.sh
	chmod +x question20.sh
	./question20.sh

python:
	python3 question15.py
	python3 question25.py
	
clean:
	rm -f $(C_BINS)
	rm -f ./question11_performance.csv ./question12_performance.csv ./question13_performance.csv
	rm -f ./question21_performance.csv ./question22_performance.csv ./question23_performance.csv ./question24_performance.csv
	rm -f ./question2511_performance.csv ./question2512_performance.csv ./question2513_performance.csv
	rm -f ./question11.pdf ./question12.pdf ./question13.pdf
	rm -f ./question21.pdf ./question22.pdf ./question23.pdf ./PlotQuestion_22_23.pdf
	rm -f ./GlobalPlotQuestion1.pdf ./GlobalPlotQuestion2.pdf ./GlobalPlotQuestion3.pdf

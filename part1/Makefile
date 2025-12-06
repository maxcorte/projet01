CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
LDFLAGS = -pthread -lrt

TARGETS = philosophes prod_cons

all: $(TARGETS)

philosophes: philosophes.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

prod_cons: prod_cons.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)


clean:
	rm -f $(TARGETS)


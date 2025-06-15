CC=gcc-14
CFLAGS= -fopenmp -Wall -Wextra -Werror -std=gnu11 -O3

all: slow medium fast

slow: slow.c
	$(CC) $(CFLAGS) -o $@ $<

medium: medium.c
	$(CC) $(CFLAGS) -o $@ $<

fast: fast.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f slow medium fast

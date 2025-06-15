CFLAGS = -Wall -Wextra -fopenmp -std=gnu11 -O3 -lm
CC = gcc

binaries = snippet1 snippet2 snippet4 snippet5 snippet6

.PHONY: all
all: clean $(binaries)



.PHONY: clean
clean:
	rm -f $(binaries) output.log

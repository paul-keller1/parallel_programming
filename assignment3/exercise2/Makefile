CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp
CC = gcc-14

.PHONY: all
all: false_sharing false_sharing_2

.PHONY: clean
clean:
	$(RM) false_sharing false_sharing_2


false_sharing: false_sharing_2.c
	$(CC) $(CFLAGS) -o $@ $^
false_sharing_2: false_sharing_2.c 
	$(CC) $(CFLAGS) -o $@ $^
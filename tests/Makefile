CFLAGS = -fopenmp -O3 -Wall -Wextra -Werror -std=gnu11
CC = gcc-14

all: sections


sections: sections.c
	$(CC) $(CFLAGS) -o sections sections.c

.PHONY: clean 
clean:
	rm sections

CFLAGS = -std=gnu11 -Wall -Wextra -lm -O3

.PHONY: all
all: column_major_hadamard_optimized row_major_hadamard_optimized

.PHONY: clean
clean:
	$(RM) column_major_hadamard_optimized row_major_hadamard_optimized

column_major_hadamard_optimized: column_major_hadamard.c
	gcc $(CFLAGS) -o column_major_hadamard_optimized column_major_hadamard.c

row_major_hadamard_optimized: row_major_hadamard.c
	gcc $(CFLAGS) -o row_major_hadamard_optimized row_major_hadamard.c

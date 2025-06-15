CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3
CC = gcc-14

.PHONY: all
all: serial  critical atomic reduction

.PHONY: clean
clean:
	$(RM) serial atomic critical reduction

serial: serial.c

atomic: atomic.c

critical: critical.c

#reduction: reduction.c
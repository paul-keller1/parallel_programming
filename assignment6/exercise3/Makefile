CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O3
CC = gcc

.PHONY: all
all: hadamard_serial hadamard_omp_default hadamard_omp_auto hadamard_omp_dynamic_1 hadamard_omp_dynamic_4 hadamard_omp_dynamic_8 hadamard_omp_dynamic_100 hadamard_omp_guided hadamard_omp_runtime

.PHONY: clean
clean:
	$(RM) hadamard_serial hadamard_omp_default hadamard_omp_auto hadamard_omp_dynamic_1 hadamard_omp_dynamic_4 hadamard_omp_dynamic_8 hadamard_omp_dynamic_100 hadamard_omp_guided hadamard_omp_runtime


hadamard_serial: hadamard_serial.c


hadamard_omp_default: hadamard_omp_default.c


hadamard_omp_auto: hadamard_omp_auto.c


hadamard_omp_dynamic_1: hadamard_omp_dynamic_1.c


hadamard_omp_dynamic_4: hadamard_omp_dynamic_4.c


hadamard_omp_dynamic_8: hadamard_omp_dynamic_8.c


hadamard_omp_dynamic_100: hadamard_omp_dynamic_100.c


hadamard_omp_guided: hadamard_omp_guided.c
hadamard_omp_runtime: hadamard_omp_runtime.c






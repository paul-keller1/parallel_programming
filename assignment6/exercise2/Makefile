CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -O3
CC = gcc

.PHONY: all
all: mandelbrot_serial mandelbrot_omp_default mandelbrot_omp_auto mandelbrot_omp_dynamic_1 mandelbrot_omp_dynamic_4 mandelbrot_omp_dynamic_8 mandelbrot_omp_dynamic_100 mandelbrot_omp_guided 

.PHONY: clean
clean:
	$(RM) mandelbrot_serial mandelbrot_omp_default mandelbrot_omp_auto mandelbrot_omp_dynamic_1 mandelbrot_omp_dynamic_4 mandelbrot_omp_dynamic_8 mandelbrot_omp_dynamic_100 mandelbrot_omp_guided mandelbrot.png


mandelbrot_serial: mandelbrot_serial.c


mandelbrot_omp_default: mandelbrot_omp_default.c


mandelbrot_omp_auto: mandelbrot_omp_auto.c


mandelbrot_omp_dynamic_1: mandelbrot_omp_dynamic_1.c


mandelbrot_omp_dynamic_4: mandelbrot_omp_dynamic_4.c


mandelbrot_omp_dynamic_8: mandelbrot_omp_dynamic_8.c


mandelbrot_omp_dynamic_100: mandelbrot_omp_dynamic_100.c


mandelbrot_omp_guided: mandelbrot_omp_guided.c





CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -march=native -Ofast --ffast-math 
CC = gcc-14

.PHONY: all
all: mandelbrot mandelbrot_parallel

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot_parallel mandelbrot.png


mandelbrot: mandelbrot.c
mandelbrot_parallel: mandelbrot_parallel.c
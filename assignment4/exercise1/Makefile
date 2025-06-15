CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp -march=native -Ofast -lpthread
CC = gcc-14

.PHONY: all
all: mandelbrot_threads mandelbrot_threads_color

.PHONY: clean
clean:
	$(RM) mandelbrot mandelbrot_threads mandelbrot.png mandelbrot_color.png


mandelbrot_threads: mandelbrot_threads.c
	$(CC) $(CFLAGS) -o mandelbrot_threads mandelbrot_threads.c

mandelbrot_threads_color: mandelbrot_threads_color.c
	$(CC) $(CFLAGS) -o mandelbrot_threads_color mandelbrot_threads_color.c

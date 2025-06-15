#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <pthread.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define X 1280
#define Y 720
#define MAX_ITER 10000


typedef struct {
    uint8_t (*image)[X];
    int start;  
    int end;    
} thread_args;


void *mandelbrot_thread(void *arg) {
    thread_args *data = (thread_args *)arg;
    float x, y, cx, cy;
    float x_min = -2.5, x_max = 1.0;
    float y_min = -1.0, y_max = 1.0;


    for (int i = data->start; i < data->end; i++) {
        for (int j = 0; j < Y; j++) {
            x = 0.0;
            y = 0.0;
            cx = x_min + (i / (float)(X - 1)) * (x_max - x_min);
            cy = y_min + (j / (float)(Y - 1)) * (y_max - y_min);
            int k;
            for (k = 0; x*x + y*y <= 4 && k < MAX_ITER; k++) {
                float x_tmp = x*x - y*y + cx;
                y = 2*x*y + cy;
                x = x_tmp;
            }
            data->image[j][i] = (uint8_t) (k * 255 / MAX_ITER);
        }
    }
    free(data);
    return NULL;
}

void calc_mandelbrot(uint8_t image[Y][X], int N) {
    pthread_t threads[N];
    int cols_per_thread = X / N;
    for (int i = 0; i < N; i++) {
        thread_args *args = malloc(sizeof(thread_args));
        args->image = image;
        args->start = i * cols_per_thread;
        args->end = (i == N - 1) ? X : (i + 1) * cols_per_thread; //this way the last thread will take care of the rest of the columns even if devision didn't divide evenly

        pthread_create(&threads[i], NULL, mandelbrot_thread, args);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Number of threads must be positive\n");
        return EXIT_FAILURE;
    }

    uint8_t image[Y][X];
    double startTime = omp_get_wtime();

    calc_mandelbrot(image, N);
    double endTime = omp_get_wtime();

    printf("Time: %2.4f seconds\n", endTime - startTime);

    const int channel_nr = 1, stride_bytes = 0;
    stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
    return EXIT_SUCCESS;
}
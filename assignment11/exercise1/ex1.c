#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2048
#define REPS 1000000

int main() {
    float *a = malloc(SIZE * sizeof(float));
    float *b = malloc(SIZE * sizeof(float));
    float *c = malloc(SIZE * sizeof(float));

    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }


    for (int i = 0; i < SIZE; ++i) {
        a[i] = 1.0f;   
        b[i] = 2.0f;   
        c[i] = 3.0f;  
    }

    clock_t start = clock();

    for (int run = 0; run < REPS; ++run) {
        for (int i = 0; i < SIZE; ++i) {
            a[i] += b[i] * c[i];
        }
    }

    clock_t end = clock();

    printf("a[0] = %f\n", a[0]);
    printf("Elapsed time: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(a); free(b); free(c);
    return 0;
}

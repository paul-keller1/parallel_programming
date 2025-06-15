#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define BLOCK_SIZE 128 / sizeof(double)

#define min(a, b) ((a) < (b) ? (a) : (b))

void matrix_multiply_original(double **c, double **a, double **b) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrix_multiply_optimized(double **c, double **a, double **b) {
    for (int ic = 0; ic < N; ic += BLOCK_SIZE) {
        for (int jc = 0; jc < N; jc += BLOCK_SIZE) {
            for (int kc = 0; kc < N; kc += BLOCK_SIZE) {
                for (int i = ic; i < min(ic + BLOCK_SIZE, N); ++i) {
                    for (int j = jc; j < min(jc + BLOCK_SIZE, N); ++j) {
                        if (kc == 0) {
                            c[i][j] = 0;
                        }
                        for (int k = kc; k < min(kc + BLOCK_SIZE, N); ++k) {
                            c[i][j] += a[i][k] * b[k][j];
                        }
                    }
                }
            }
        }
    }
}

double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    double **a = malloc(N * sizeof(double *));
    double **b = malloc(N * sizeof(double *));
    double **c_original = malloc(N * sizeof(double *));
    double **c_optimized = malloc(N * sizeof(double *));

    for (int i = 0; i < N; ++i) {
        a[i] = malloc(N * sizeof(double));
        b[i] = malloc(N * sizeof(double));
        c_original[i] = malloc(N * sizeof(double));
        c_optimized[i] = malloc(N * sizeof(double));
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
            c_original[i][j] = 0;
            c_optimized[i][j] = 0;
        }
    }

    struct timespec start, end;



        // Time original
    clock_gettime(CLOCK_MONOTONIC, &start);
    matrix_multiply_original(c_original, a, b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    matrix_multiply_optimized(c_optimized, a, b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));


    int mismatches = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (c_original[i][j] != c_optimized[i][j]) {
                mismatches++;
                if (mismatches < 5) {
                    printf("Mismatch at c[%d][%d]: Original = %f, Optimized = %f\n",
                           i, j, c_original[i][j], c_optimized[i][j]);
                }
            }
        }
    }

    if (mismatches == 0) {
        puts("✅ Results match for matrix multiplication.");
    } else {
        printf("❌ Mismatch found for matrix multiplication. Total mismatches: %d\n", mismatches);
    }

    for (int i = 0; i < N; ++i) {
        free(a[i]);
        free(b[i]);
        free(c_original[i]);
        free(c_optimized[i]);
    }
    free(a);
    free(b);
    free(c_original);
    free(c_optimized);

    return 0;
}
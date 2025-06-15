#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_SUMS 10000000

void sum_arrays_original(const int *a, const int *b, const int *c, long long *sum_a, long long *sum_b, long long *sum_c) {
    *sum_a = 0;
    *sum_b = 0;
    *sum_c = 0;

    for (int i = 0; i < N_SUMS; ++i) {
        *sum_a += a[i];
        *sum_b += b[i];
        *sum_c += c[i];
    }
}

void sum_arrays_optimized(const int *a, const int *b, const int *c, long long *sum_a, long long *sum_b, long long *sum_c) {
    *sum_a = 0;
    *sum_b = 0;
    *sum_c = 0;

    for (int i = 0; i < N_SUMS; ++i) {
        *sum_a += a[i];

    }
    for (int i = 0; i < N_SUMS; ++i) {

        *sum_b += b[i];

    }
    for (int i = 0; i < N_SUMS; ++i) {

        *sum_c += c[i];
    }
}


double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    int *array1 = malloc(N_SUMS * sizeof(int));
    int *array2 = malloc(N_SUMS * sizeof(int));
    int *array3 = malloc(N_SUMS * sizeof(int));

    srand((unsigned)time(NULL));
    for (int i = 0; i < N_SUMS; ++i) {
        array1[i] = rand() % 100;
        array2[i] = rand() % 100;
        array3[i] = rand() % 100;
    }

    long long sum_a_orig = 0, sum_b_orig = 0, sum_c_orig = 0;
    long long sum_a_opt = 0, sum_b_opt = 0, sum_c_opt = 0;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    sum_arrays_original(array1, array2, array3, &sum_a_orig, &sum_b_orig, &sum_c_orig);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    sum_arrays_optimized(array1, array2, array3, &sum_a_opt, &sum_b_opt, &sum_c_opt);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));


    if (sum_a_orig == sum_a_opt && sum_b_orig == sum_b_opt && sum_c_orig == sum_c_opt) {
        puts("✅ Results match for sum_arrays example.");
    } else {
        puts("❌ Mismatch found for sum_arrays example.");
    }


    free(array1);
    free(array2);
    free(array3);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MIN_SUM 10000000

void min_and_sum_original(const int *a, int *min_val, long long *sum_val) {
    *min_val = a[0];
    *sum_val = 0;
    for (int i = 1; i < N_MIN_SUM; ++i) {
        *min_val = (a[i] < *min_val) ? a[i] : *min_val;
    }

    for (int i = 0; i < N_MIN_SUM; ++i) {
        *sum_val += a[i];
    }
}

void min_and_sum_optimized(const int *a, int *min_val, long long *sum_val) {
    // You will implement your optimization here
    *min_val = a[0];
    *sum_val = a[0];
    for (int i = 1; i < N_MIN_SUM; ++i) {
        *min_val = (a[i] < *min_val) ? a[i] : *min_val;
        *sum_val += a[i];
    }
}


double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    int *array_data = malloc(N_MIN_SUM * sizeof(int));

    srand((unsigned)time(NULL));
    for (int i = 0; i < N_MIN_SUM; ++i) {
        array_data[i] = rand() % 1000;
    }

    int min_orig = 0;
    long long sum_orig = 0;
    int min_opt = 0;
    long long sum_opt = 0;

    struct timespec start, end;


        clock_gettime(CLOCK_MONOTONIC, &start);
    min_and_sum_original(array_data, &min_orig, &sum_orig);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    min_and_sum_optimized(array_data, &min_opt, &sum_opt);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));


    if (min_orig == min_opt && sum_orig == sum_opt) {
        puts("✅ Results match for min_and_sum example.");
    } else {
        puts("❌ Mismatch found for min_and_sum example.");
    }

    free(array_data);
    return 0;
}
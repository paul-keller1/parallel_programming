#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void process_array_original(int *a, const int *b, const int *c) {
    for (int i = 0; i < N; i++) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
  }
    
}

void process_array_splitted(int *a, const int *b, const int *c) {
  for (int i = 0; i < N; i += 2) {
            a[i] = c[i] + 5;
    }
  for (int i = 1; i < N; i += 2) {
            a[i] = b[i] + 4;
    }
}

int main() {
    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));
    int *c = malloc(N * sizeof(int));

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; ++i) {
        b[i] = rand() % 100;
        c[i] = rand() % 100;
    }

    struct timespec start, end;

    printf("Running process_array_original...\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_original(a, b, c);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original process_array time: %.6f seconds\n", elapsed(start, end));

    int *a_original = malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i) {
        a_original[i] = a[i];
    }



    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_original(a_original, b, c);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_splitted(a, b, c);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));


    int mismatch_count = 0;
    for (int i = 0; i < N; ++i) {
        if (a[i] != a_original[i]) {
            mismatch_count++;
            if (mismatch_count < 10) {
                printf("Mismatch at index %d: original=%d, optimized=%d\n", i, a_original[i], a[i]);
            }
        }
    }

    if (mismatch_count == 0) {
        puts("✅ Results match for process_array example.");
    } else {
        printf("❌ Mismatch found for process_array example. Total mismatches: %d\n", mismatch_count);
    }

    free(a);
    free(b);
    free(c);
    free(a_original);

    return 0;
}
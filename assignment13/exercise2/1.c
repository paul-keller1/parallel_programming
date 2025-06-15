#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000001  // Must be odd

void original(int *a, const int *b) {
    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }
}

// Incorrect loop unrolling – kept as-is for demonstration
void optimized(int *a, const int *b) {

    for (int i = 0; i < N - 2; i += 2) {
        a[i] = b[i] + b[i + 1];
        a[i + 1] = b[i + 1] + b[i + 2];
    }
}

double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void print_array(const char *label, const int *arr, int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *a_orig = malloc((N - 1) * sizeof(int));
    int *a_opt  = malloc((N - 1) * sizeof(int));
    int *b      = malloc(N * sizeof(int));

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; ++i) {
        b[i] = rand() % 100;
    }

    struct timespec start, end;

    // Time original
    clock_gettime(CLOCK_MONOTONIC, &start);
    original(a_orig, b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    optimized(a_opt, b);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));



    // Check correctness
    int ok = 1;
    for (int i = 0; i < N - 1; ++i) {
        if (a_orig[i] != a_opt[i]) {
            printf("Mismatch at %d: %d vs %d\n", i, a_orig[i], a_opt[i]);
            ok = 0;
        }
    }
    if (ok) puts("✅ Results match.");
    else    puts("❌ Mismatch found.");

    free(a_orig);
    free(a_opt);
    free(b);
    return 0;
}

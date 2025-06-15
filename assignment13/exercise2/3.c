#include <math.h>  // For hypot
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CONDITIONAL 10000000

void process_array_conditional_original(int *a, const int *b, const int *c, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        if (array_size % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }
}

// Your task: Create an optimized version here
void process_array_conditional_optimized(int *a, const int *b, const int *c, int array_size) {
    // Hint: Look at the condition `if (array_size % 2)`. Does it change during the loop?
    if (array_size % 2) {
        for (int i = 0; i < array_size; ++i) {
            a[i] = b[i] + 5;
        }
    } else {
        for (int i = 0; i < array_size; ++i) {
            a[i] = c[i] + 5;
        }
    }
}

double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void print_array(const char *label, const int *arr, int size) {
    printf("%s: ", label);
    for (int i = 0; i < (size > 10 ? 10 : size); ++i) {
        printf("%d ", arr[i]);
    }
    if (size > 10) printf("...");
    printf("\n");
}

int main() {
    int *a_orig_cond = malloc(N_CONDITIONAL * sizeof(int));
    int *a_opt_cond = malloc(N_CONDITIONAL * sizeof(int));
    int *b_cond = malloc(N_CONDITIONAL * sizeof(int));
    int *c_cond = malloc(N_CONDITIONAL * sizeof(int));

    srand((unsigned)time(NULL));
    for (int i = 0; i < N_CONDITIONAL; ++i) {
        b_cond[i] = rand() % 100;
        c_cond[i] = rand() % 100 + 100;
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_conditional_original(a_orig_cond, b_cond, c_cond, N_CONDITIONAL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_conditional_optimized(a_opt_cond, b_cond, c_cond, N_CONDITIONAL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));

    int ok_cond = 1;
    for (int i = 0; i < N_CONDITIONAL; ++i) {
        if (a_orig_cond[i] != a_opt_cond[i]) {
            printf("Conditional Mismatch at %d: %d vs %d\n", i, a_orig_cond[i], a_opt_cond[i]);
            ok_cond = 0;
            break;
        }
    }
    if (ok_cond)
        puts("✅ Results match for conditional example.");
    else
        puts("❌ Mismatch found for conditional example.");

    free(a_orig_cond);
    free(a_opt_cond);
    free(b_cond);
    free(c_cond);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // For hypot

#define N 10000000 // Number of elements for this specific example

// --- Original function using hypot inside the loop ---
void process_array_hypot_original(double *a) {
    for (int i = 0; i < N; ++i) {
      a[i] *= hypot(0.3, 0.4);
  }
}

void process_array_hypot_optimized(double *a) {
  double hyp = hypot(0.3, 0.4);
    for (int i = 0; i < N; ++i) {
        a[i] *= hyp;
    }
}


double elapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void print_array(const char *label, const double *arr, int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("...\n"); // Added '...' for brevity with large arrays
}

int main() {
    double *array_orig = malloc(N* sizeof(double));
    double *array_opt  = malloc(N * sizeof(double));

    // Initialize arrays
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; ++i) {
        array_orig[i] = (double)rand() / RAND_MAX * 100.0; // Random doubles
        array_opt[i]  = array_orig[i]; // Make sure both start with the same values
    }

    struct timespec start, end;

    // Time original



        clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_hypot_original(array_orig);

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Original time:  %.6f seconds\n", elapsed(start, end));

    // Time optimized
    clock_gettime(CLOCK_MONOTONIC, &start);
    process_array_hypot_optimized(array_opt); // Call your optimized function

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Optimized time: %.6f seconds\n", elapsed(start, end));



    // Check correctness (uncomment when you have your optimized function)
    int ok = 1;
    for (int i = 0; i < N; ++i) {
        // Using a small epsilon for floating-point comparison
        if (fabs(array_orig[i] - array_opt[i]) > 1e-9) {
            printf("Mismatch at %d: %.10lf vs %.10lf\n", i, array_orig[i], array_opt[i]);
            ok = 0;
            break; // Stop at first mismatch
        }
    }
    if (ok) puts("✅ Results match for hypot example.");
    else    puts("❌ Mismatch found for hypot example.");


    free(array_orig);
    free(array_opt);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {

    int N = 1000;
    int use_parallel_init = 1; // Set to 0 to test without first-touch

    if (argc < 2 || argc > 3) {
        printf("Usage: %s <N> [0|1=use_parallel_init]\n", argv[0]);
        return EXIT_FAILURE;
    }

    N = atoi(argv[1]);
    if (argc == 3) use_parallel_init = atoi(argv[2]);

    long long **matrix;
    double start_time, end_time;

    // Allocate memory for the 2D array
    start_time = omp_get_wtime();
    matrix = (long long **)malloc(N * sizeof(long long *));
    for (int i = 0; i < N; i++) {
        matrix[i] = (long long *)malloc(N * sizeof(long long));
    }
    end_time = omp_get_wtime();
    printf("Memory allocation time: %f seconds\n", end_time - start_time);

    // Initialize the matrix — first-touch vs. non-first-touch
    if (use_parallel_init) {
        printf("Using parallel (first-touch) initialization\n");
        start_time = omp_get_wtime();
        #pragma omp parallel for default(none) shared(matrix, N)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i + j;
            }
        }
        end_time = omp_get_wtime();
        printf("Parallel initialization time: %f seconds\n", end_time - start_time);
    } else {
        printf("Using serial (no first-touch) initialization\n");
        start_time = omp_get_wtime();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i + j;
            }
        }
        end_time = omp_get_wtime();
        printf("Serial initialization time: %f seconds\n", end_time - start_time);
    }

    // Matrix computation
    long long sum = 0.0;
    start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += matrix[i][j];
        }
    }
    end_time = omp_get_wtime();
    printf("Matrix computation time: %f seconds\n", end_time - start_time);

    printf("Sum of matrix elements: %lld\n", sum);

    // Memory cleanup
    start_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
    end_time = omp_get_wtime();
    printf("Memory deallocation time: %f seconds\n", end_time - start_time);

    return EXIT_SUCCESS;
}

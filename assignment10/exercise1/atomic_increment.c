#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 

#define N_ITERATIONS 500000000LL // Using LL for long long literal

int main() {
    long long counter = 0; // Use long long to prevent overflow for large N_ITERATIONS
    double start_time, end_time;

    start_time = omp_get_wtime();

    // Parallelize the loop using OpenMP
    // The 'atomic' directive ensures thread-safe incrementing of 'counter'
    #pragma omp parallel for
    for (long long i = 0; i < N_ITERATIONS; ++i) {
        #pragma omp atomic
        counter++;
    }


    end_time = omp_get_wtime();

    printf("time: %.6f\n", end_time - start_time);

    return 0;
}

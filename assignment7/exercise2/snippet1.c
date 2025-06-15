#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define N 10000000

int main() {
    int* x = malloc(N * sizeof(int));
    int* y = malloc(N * sizeof(int));



    for (int i = 0; i < N - 1; i++) {
        x[i] = rand() % INT_MAX;
        y[i] = rand() % INT_MAX;
    }

    double factor = 1;

    // unparallelized execution
    double startTime = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        x[i] = factor * y[i];
        factor = factor / 2;
    }

    double endTime = omp_get_wtime();
    printf("Unparallelized execution: %f\n", endTime - startTime);

    // here the -03 "unparallelized" execution was faster than this implementation
    factor = 1;
    startTime = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        x[i] = (factor / (1 << i)) * y[i];
    }

    endTime = omp_get_wtime();
    printf("parallelized execution: %f\n", endTime - startTime);
}




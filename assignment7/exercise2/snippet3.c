#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define N 10000000

int main() {
    int* x = malloc(N * sizeof(int));
    int* y = malloc(N * sizeof(int));



    double twice = 1;




    for (int i = 0; i < N - 1; i++) {
        x[i] = rand() % INT_MAX;
        y[i] = rand() % INT_MAX;
    }

    // unparallelized execution
    double startTime = omp_get_wtime();
    x[0] = x[0] + 5 * y[0];
    for (int i = 1; i < N; i++) {
        x[i] = x[i] + 5 * y[i];
        if (twice) {
            x[i - 1] = 2 * x[i - 1];
        }
    }
    double endTime = omp_get_wtime();
    printf("Unparallelized execution, flag set: %f\n", endTime - startTime);


    twice = 0;

    startTime = omp_get_wtime();
    x[0] = x[0] + 5 * y[0];
    for (int i = 1; i < N; i++) {
        x[i] = x[i] + 5 * y[i];
        if (twice) {
            x[i - 1] = 2 * x[i - 1];
        }
    }

    endTime = omp_get_wtime();
    printf("Unparallelized execution, flag not set: %f\n", endTime - startTime);

    twice = 1;
    
    printf("program can't be parallelized if flag set.\n");
    
    twice = 0;

    // parallelized execution
    startTime = omp_get_wtime();
    x[0] = x[0] + 5 * y[0];
    #pragma omp parallel for
    for (int i = 1; i < N; i++) {
        x[i] = x[i] + 5 * y[i];
        if (twice) {
            x[i - 1] = 2 * x[i - 1];
        }
    }
    endTime = omp_get_wtime();
    printf("parallelized execution, flag not set: %f\n", endTime - startTime);
}

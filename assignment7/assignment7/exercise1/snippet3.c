
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define N 100000000

int main() {
    int* x = malloc(N * sizeof(int));
    int* y = malloc(N * sizeof(int));


    int a = 5;
    int b = 17;

    for (int i = 0; i < N - 1; i++) {
        x[i] = rand() % INT_MAX;
        y[i] = rand() % INT_MAX;
    }

    // unparallelized execution
    double startTime = omp_get_wtime();
    for (int i=0; i < N; i++) {
      x[i] = y[i] * 2 + b * i;
    }
    
    
    for (int i=0; i < N; i++) {
      y[i] = x[i]  + a / (i+1);
    }
    double endTime = omp_get_wtime();
    printf("Unparallelized execution: %f\n", endTime - startTime);


    // parallelized execution
    startTime = omp_get_wtime();
    #pragma omp parallel for
    for (int i=0; i < N; i++) {
      x[i] = y[i] * 2 + b * i;
    }
    
    #pragma omp parallel for
    for (int i=0; i < N; i++) {
      y[i] = x[i]  + a / (i+1);
    }
    endTime = omp_get_wtime();
    printf("parallelized execution: %f\n", endTime - startTime);
}





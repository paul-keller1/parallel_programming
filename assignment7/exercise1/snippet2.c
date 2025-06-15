#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


#define N 100000000

int main() {
    int* x = malloc(N * sizeof(int));
    int* y = malloc(N * sizeof(int));

    int* z = malloc(N * sizeof(int));

    int a = 5;
    int f;
    int k = 5;

    for (int i = 0; i < N - 1; i++) {
        x[i] = rand() % INT_MAX;
        y[i] = rand() % INT_MAX;
    }

    // unparallelized execution
    //achtung a ist nicht unbedingt privat und könnte von außen geändert werden
    double startTime = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        a = (x[i] + y[i]) / (i + 1);
        z[i] = a;
    }

    f = sqrt(a + k);
    double endTime = omp_get_wtime();
    printf("Unparallelized execution: %f\n", endTime - startTime);


    // parallelized execution
    startTime = omp_get_wtime();
    #pragma omp for
    for (int i = 0; i < N; i++) {
      z[i] = (x[i] + y[i]) / (i + 1);
        
    }

    f = sqrt(z[N-1] + k);
    endTime = omp_get_wtime();
    printf("parallelized execution: %f\n", endTime - startTime);
}



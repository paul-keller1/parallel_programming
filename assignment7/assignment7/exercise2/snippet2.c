#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 10000000

int main() {
    int* x = malloc(N * sizeof(int));
    int* y = malloc(N * sizeof(int));
    int* z = malloc(N * sizeof(int));

    for (int i = 0; i < N - 1; i++) {
        x[i] = rand() % INT_MAX;
        y[i] = rand() % INT_MAX;
        z[i] = rand() % INT_MAX;
    }

    // unparallelized execution
    double startTime = omp_get_wtime();
    for (int i = 1; i<N; i++) {
      x[i] = (x[i] + y[i-1]) / 2;
      y[i] = y[i] + z[i] * 3;
  }
    double endTime = omp_get_wtime();
    printf("unparallelized execution: %f\n", endTime-startTime);
    printf("Can't be parallelized!\n");
}





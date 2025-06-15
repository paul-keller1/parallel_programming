
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define N 2000




int main() {
    int a[N], b[N];
    int i;
    double x;
    for(int i = 0; i < N; i++) {
      b[N] = i;
    }


    double startTime = omp_get_wtime();

  

    #pragma omp parallel for default(none)
    for (i=0; i<N; i++) {
        x = sqrt(b[i]) - 1;
        a[i] = x*x + 2*x + 1;
    }

    double endTime = omp_get_wtime();

    printf("time: %2.4f seconds\n", endTime-startTime);

    return EXIT_SUCCESS;
}
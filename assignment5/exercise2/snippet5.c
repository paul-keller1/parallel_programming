
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#define N 2000




int main() {
    int b[N];
    int i;

    double startTime = omp_get_wtime();

    for (int j = 0; j < N; j++) {
      b[j] = j+1;
    }
    

    //result should be N*(N+1)/2 little gauss
    long sum = 0; 
    #pragma omp parallel for
    for (i=0; i<N; i++) {
        sum = sum + b[i];
    }

    long sum_serial = 0;
    for(i=0; i<N; i++) {
      sum_serial = sum_serial + b[i];
    }

    double endTime = omp_get_wtime();
    printf("\nSNIPPET5\n");
    printf("time: %2.4f seconds\n", endTime-startTime);
    printf("sum: %ld, sum_serial: %ld", sum, sum_serial);

    return EXIT_SUCCESS;
}
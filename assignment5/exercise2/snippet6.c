
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#define N 100




int main() {
    int a[N], b[N];
    int i, j;


    for (int j = 0; j < N; j++) {
        b[j] = j+1;
      }
      

    double startTime = omp_get_wtime();

  

    #pragma omp parallel
    #pragma omp for
    for (i=0; i<N; i++) {
        #pragma omp for
        for (j=0; j<N; j++) {
            a[i][j] = b[i][j];
        }
    }


    double endTime = omp_get_wtime();

    printf("time: %2.4f seconds\n", endTime-startTime);

    return EXIT_SUCCESS;
}
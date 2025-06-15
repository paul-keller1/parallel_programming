
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#define N 2000
#define TRIALS 200




int main() {
    int a[N], b[N];
    int i;
    for (int i = 0; i < N; i++) {
      b[i] = i;
    }
    
    int x;
    int f = 2;
    int results[TRIALS];
    double startTime;
    double endTime;
    for (int j = 0; j < TRIALS; j++){
      startTime = omp_get_wtime(); //just tracking once
      #pragma omp parallel for private(f,x)
      for (i=0; i<N; i++) {
          x = f * b[i];
          a[i] = x - 7;
      }
      endTime = omp_get_wtime();
      a[0] = x; 
      results[j] = a[0];
    }


    printf("\nSNIPPET4\n");
    printf("time: %2.4f seconds\n", endTime-startTime);
    printf("Value of x in the end of the parallel section: %d\n",a[N-1] + 7);
    printf("Values of a[0] outside\n");
    for (int i = 0; i < TRIALS; i++) {
      if (i != TRIALS-1) {
        printf("%d, ", results[i]);
        
      } else {
        printf("%d\n", results[i]);

      }
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long n = 70000000;
    long count = 0;
    double x, y, pi;
    double startTime, endTime;
    
    startTime = omp_get_wtime();
    
    srand((unsigned) time(NULL));
    #pragma omp parallel for default(none) reduction(+: count) shared(n) private(x, y) //pay attention to positioning of default(none)
      for (long i = 0; i < n; i++) {
          x = (double) rand() / RAND_MAX;
          y = (double) rand() / RAND_MAX;
  
          if (x * x + y * y <= 1) count++;
      } 

    

    endTime = omp_get_wtime();

    pi = 4.0 * count / n;
    printf("Approximate value of pi: %f\n", pi);
	  printf("time: %2.4f seconds\n", endTime-startTime);
    
    return 0;
}
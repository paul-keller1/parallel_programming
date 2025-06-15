#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <limits.h>


#define N 100000000

int main() {

  int * x = malloc(N*sizeof(int));
  int * y = malloc(N*sizeof(int));

  int * x1 = malloc(N*sizeof(int));

  for (int i=0; i < N-1; i++) {
    x[i] = rand() % INT_MAX;
    y[i] = rand() % INT_MAX;

  }

    


  //unparallelized execution
  double startTime = omp_get_wtime();
  for (int i=0; i < N-1; i++) {
    x[i] = (y[i] + x[i+1]) / 7;
  }
  double endTime = omp_get_wtime();
  printf("Unparallelized execution: %f\n", endTime-startTime);


  startTime = omp_get_wtime();
  #pragma omp parallel for 
  for (int i=0; i < N-1; i++) {
    x1[i] = (y[i] + x[i+1]) / 7;
  }
  
  #pragma omp parallel for 
  for (int i=0; i < N-1; i++) {
    x[i] = (y[i] + x1[i+1]) / 7;
  }
  endTime = omp_get_wtime();
  printf("parallelized execution: %f\n", endTime-startTime);





}





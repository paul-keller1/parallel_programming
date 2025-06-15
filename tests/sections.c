#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int a[1000], b[1000];
  #pragma omp parallel 
  {
    #pragma omp sections
    {
      #pragma omp section
      for (int i = 0; i < 1000; i++)
        a[i] = 100;
      #pragma omp section
      for (int i = 0; i < 1000; i++)
        b[i] = 200;
    }
  }
  for (int i = 0; i < 1000; i++)
    printf("%d %d\n", a[i], b[i]);

  return EXIT_SUCCESS;
}
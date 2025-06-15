#include <stdio.h>
#include <stdlib.h>
#include <omp.h>



int main(int args, char ** argv) {
  if(args != 2) {
    printf("Wrong input format\n");
    return EXIT_FAILURE;
  }

  long n = strtol(argv[1], NULL, 10);
  if(n == 0) {
    printf("couldn't parse input\n");
    return EXIT_FAILURE;
  }
  printf("start\n");
  fflush(stdout);

  int32_t** a = malloc(n * sizeof(int32_t*));
  int32_t** b = malloc(n * sizeof(int32_t*));
  int32_t** c = malloc(n * sizeof(int32_t*));
  if (!a || !b || !c) {
    printf("Memory allocation failed\n");
    return EXIT_FAILURE;
  }
  for (int32_t i = 0; i < n; i++) {
    a[i] = malloc(n * sizeof(int32_t));
    b[i] = malloc(n * sizeof(int32_t));
    c[i] = malloc(n * sizeof(int32_t));
    if (!a[i] || !b[i] || !c[i]) {
      printf("Memory allocation failed\n");
      return EXIT_FAILURE;
    }
  }


  printf("allocated\n");
  fflush(stdout);

  
  for (int32_t i = 0; i < n; ++i) {
    for (int32_t j = 0; j < n; ++j) {
        a[i][j] = 5;
        b[i][j] = 5;
        c[i][j] = 0;
    }
  }

  printf("initialized\n");
  fflush(stdout);

  double startTime = omp_get_wtime();

  for (int32_t i = 0; i < n; ++i) {
    for (int32_t j = 0; j < n; ++j) {
        c[i][j] = a[i][j] * b[i][j];
    }
    
  }

  double endTime = omp_get_wtime();

  printf("check: %d\n", c[0][0]);
  printf("time: %f\n", endTime - startTime);

  // free memory
  for (int32_t i = 0; i < n; i++) {
    free(a[i]);
    free(b[i]);
    free(c[i]);
  }
  free(a);
  free(b);
  free(c);

  return EXIT_SUCCESS;
}


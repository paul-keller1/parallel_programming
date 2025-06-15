#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100

int main() {
    int a[N], b[N], b_serial[N];
    int i;

    // Parallel computation
    double startTime = omp_get_wtime();

    a[0] = 0;
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 1; i < N; i++) {
            a[i] = 3 * i * (i + 1);
        }
        #pragma omp for
        for (i = 1; i < N; i++) {
            b[i] = a[i] - a[i-1];
        }
    }
    double endTime = omp_get_wtime();


    double startTimeSerial = omp_get_wtime();
    a[0] = 0;
    for (i = 1; i < N; i++) {
        a[i] = 3 * i * (i + 1);
        b_serial[i] = a[i] - a[i-1];
    }
    double endTimeSerial = omp_get_wtime();


    printf("\nSNIPPET2\n");
    printf("time parallel: %2.4f seconds\n", endTime - startTime);
    printf("time serial  : %2.4f seconds\n", endTimeSerial - startTimeSerial);



    printf("All values of b (parallel): ");
    for (i = 0; i < N; i++) {
        printf("%d", b[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("\n");


    printf("All values of b_serial (serial): ");
    for (i = 0; i < N; i++) {
        printf("%d", b_serial[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}
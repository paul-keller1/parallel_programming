#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100

int main() {
    long long a[N], b[N];
    long long b_serial[N];
    int i;

    double startTime = omp_get_wtime();

    a[0] = 0;
    #pragma omp parallel for
    for (i = 1; i < N; i++) {
        a[i] = 2.0 * i * (i - 1);
        b[i] = a[i] - a[i - 1];
    }

    double endTime = omp_get_wtime();

    double startTimeSerial = omp_get_wtime();

    a[0] = 0;
    for (i = 1; i < N; i++) {
        a[i] = 2.0 * i * (i - 1);
        b_serial[i] = a[i] - a[i - 1];
    }

    double endTimeSerial = omp_get_wtime();

    printf("\nSNIPPET1\n");
    printf("time parallel: %2.4f seconds\n", endTime - startTime);
    printf("time serial: %2.4f seconds\n", endTimeSerial - startTimeSerial);
    // printf("result parallel b[N-1]: %lld\n", b[N - 1]);
    // printf("result serial b[N-1]: %lld\n", b_serial[N - 1]);


    printf("All values of b: ");
    for (i = 0; i < N; i++) {
        printf("%lld", b[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("\nAll values of b_serial: ");
    for (i = 0; i < N; i++) {
        printf("%lld", b_serial[i]);
        if (i < N - 1) {
            printf(", ");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}
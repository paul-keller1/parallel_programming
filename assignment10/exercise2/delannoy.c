#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long delannoy_seq(int m, int n) {
    if (m == 0 || n == 0) return 1;
    return delannoy_seq(m-1, n) + delannoy_seq(m-1, n-1) + delannoy_seq(m, n-1);
}

long long delannoy_parallel(int m, int n) {
    if (m == 0 || n == 0) return 1;
    long long x = 0, y = 0, z = 0;

    #pragma omp task shared(x)
    x = delannoy_parallel(m-1, n);

    #pragma omp task shared(y)
    y = delannoy_parallel(m-1, n-1);

    #pragma omp task shared(z)
    z = delannoy_parallel(m, n-1);

    #pragma omp taskwait
    return x + y + z;
}

int main(int argc, char *argv[]) {
    int N = (argc > 1) ? atoi(argv[1]) : 12;

    double t1 = omp_get_wtime();
    long long seq = delannoy_seq(N, N);
    double t2 = omp_get_wtime();
    printf("Sequential: D(%d, %d) = %lld, time = %.3f seconds\n", N, N, seq, t2 - t1);

    long long par;
    double t3 = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        par = delannoy_parallel(N, N);
    }
    double t4 = omp_get_wtime();
    printf("Parallel:   D(%d, %d) = %lld, time = %.3f seconds\n", N, N, par, t4 - t3);

    return 0;
}

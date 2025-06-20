#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#define N 1000

void a(unsigned c1) {
    unsigned c2 = 32 * c1;
    printf("a): %u\n", c2);
}

void a_solution(unsigned c1) {
    unsigned c2 = c1 << 5;
    printf("a): solution %u\n", c2);
}

void b(unsigned c1) {
    unsigned c2 = 15 * c1;
    printf("b): %u\n", c2);
}

void b_solution(unsigned c1) {
    unsigned c2 = (c1 << 4) - c1;
    printf("b): solution %u\n", c2);
}

void c(unsigned c1) {
    unsigned c2 = 96 * c1;
    printf("c): %u\n", c2);
}

void c_solution(unsigned c1) {
    unsigned c2 = (c1 << 6) + (c1 << 5);
    printf("c): solution %u\n", c2);
}

void d(unsigned c1) {
    unsigned c2 = 0.125 * c1;
    printf("d): %u\n", c2);
}

void d_solution(unsigned c1) {
    unsigned c2 =  c1 >> 3;
    printf("d): solution %u\n", c2);
}

void e(unsigned *a) {
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[5 * i];
    }
    printf("e): %u\n", sum_fifth);
}

void e_solution(unsigned *a) {
    unsigned sum_fifth = 0;
    int T = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[T];
        T += 5;
    }
    printf("e): solution %u\n", sum_fifth);
}


void f(double *a) {
    for (int i = 0; i < N; ++i) {
        a[i] += i / 5.3;
    }
    printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void f_solution(double *a) {
    double T = 1 / 5.3;
    for (int i = 0; i < N; ++i) {
        a[i] += i * T;
    }
    printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void g(float c1) {
    float c2 = -1 * c1;
    printf("g): %f\n", c2);
}

void g_solution(float c1) {
    uint32_t *p = (uint32_t*)&c1;
    *p ^= 0x80000000;  // Toggle the sign bit

    // Now c1 is the new float with sign bit flipped
    printf("g): solution %f\n", *p, c1);
}

int main(void) {
    a(100);
    a_solution(100);
    b(100);
    b_solution(100);
    c(100);
    c_solution(100);
    d(100);
    d_solution(100);
    unsigned a[1000];
    for(int i = 0; i < 1000; i++) {
        a[i] = 5;
    }
    e(a);
    e_solution(a);
    g(100);
    g_solution(100);
    return EXIT_SUCCESS;
}

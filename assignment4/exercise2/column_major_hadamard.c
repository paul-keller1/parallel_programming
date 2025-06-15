#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define N 2866  // Change matrix size as needed //N*N*3*4= 8*(12000000 + 256000 + 32000 + 32000) = 8*12322000 Byte ->8*12322000 / (3*4) = 8214664 Bytes = N*N -> N = 2866

int32_t a[N][N], b[N][N], c[N][N];

void initialize_matrices() {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0;
        }
    }
}

void column_major_access() {
    for (size_t j = 0; j < N; ++j) {
        for (size_t i = 0; i < N; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}




int main() {
    srand(time(NULL));
    initialize_matrices();

    
    return 0;
}

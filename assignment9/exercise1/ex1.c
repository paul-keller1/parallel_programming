#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
    do {                   \
        PERROR;            \
        goto label;        \
    } while (0)

#define INIT_ARRAY(arr, label)                   \
    do {                                         \
        if (!(arr)) PERROR_GOTO(label);          \
        for (long i = 0; i < n; ++i) {           \
            arr[i] = calloc(n, sizeof(**(arr))); \
            if (!arr[i]) PERROR_GOTO(label);     \
        }                                        \
    } while (0)

void free_2d_array_long(long **arr, long len) {
    if (!arr) {
        return;
    }
    for (long i = 0; i < len; ++i) {
        if (!arr[i]) {
            break;
        }
        free(arr[i]);
    }
    free(arr);
}

void free_2d_array_long_long(long long **arr, long len) {
    if (!arr) {
        return;
    }
    for (long i = 0; i < len; ++i) {
        if (!arr[i]) {
            break;
        }
        free(arr[i]);
    }
    free(arr);
}

int main(int argc, char **argv) {
    // handle input
    if (argc != 2) {
        fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    errno = 0;
    char *str = argv[1];
    char *endptr;
    long n = strtol(str, &endptr, 0);
    if (errno != 0) {  // includes to long input with errno == ERANGE
        perror("strtol");
        return EXIT_FAILURE;
    }
    if (endptr == str) {
        fprintf(stderr, "Error: no digits were found!\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Error: matrix size must not be negative!\n");
        return EXIT_FAILURE;
    }

    // allocate memory
    int status = EXIT_FAILURE;
    long **a = calloc(n, sizeof(*a));
    INIT_ARRAY(a, error_a);
    long **b = calloc(n, sizeof(*b));
    INIT_ARRAY(b, error_b);
    long long **c = calloc(n, sizeof(*c));
    INIT_ARRAY(c, error_c);
    unsigned *local_res = calloc(omp_get_max_threads(), sizeof(*local_res));
    if (!local_res) PERROR_GOTO(error_local_res);
    status = EXIT_SUCCESS;

    // fill matrix
    srand(7);
    for (long i = 0; i < n; ++i) {
        for (long j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    double start_time = omp_get_wtime();

    // matrix multiplication
		#pragma omp parallel for default(none) shared(n, a, b, c)
				for (long i = 0; i < n; ++i) {
						for (long j = 0; j < n; ++j) {
								for (long k = 0; k < n; ++k) {
										c[i][j] += (long long)a[i][k] * (long long)b[k][j];
								}
						}
				}
		//addition of all elements in multiplication-matrix as check sum
		unsigned long long res = 0;
		#pragma omp parallel for default(none) shared(n, a, b, c, local_res)
			for (long i = 0; i < n; ++i) {
				for (long j = 0; j < n; ++j) {
					local_res[omp_get_thread_num()] += c[i][j];
				}
			}
	
		for (int l = 0; l < omp_get_num_threads(); ++l) {
			res += local_res[l];
		}
		double end_time = omp_get_wtime();
		printf("res: %llu, time: %2.2f seconds\n", res, end_time - start_time);

    // cleanup
error_local_res:
    free(local_res);
error_c:
    free_2d_array_long_long(c, n);
error_b:
    free_2d_array_long(b, n);
error_a:
    free_2d_array_long(a, n);
    return status;
}
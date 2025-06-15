#include <omp.h>
#include <stdio.h>

int main() {
    for (int iter = 0; iter < 1000; iter++) {
        int data;
        int flag = 0;
        
        #pragma omp parallel num_threads(2)
        {
            int tid = omp_get_thread_num();
            if (tid == 0) {
                data = 42;
                flag = 1;
            } else if(tid == 1) {
                int flag_val = 0;
                while (flag_val < 1) {
                    flag_val = flag;
                }
                printf("Iteration %d: flag=%d, data=%d\n", iter, flag, data);
            }
        }
    }
    
    return 0;
}

//"rewrite this to try the parallel region 100 times" for copilot in the ex1.c
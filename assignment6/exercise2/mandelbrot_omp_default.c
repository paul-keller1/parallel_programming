

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
    float x, y, cx, cy;
    float x_min = -2.5, x_max = 1.0;
    float y_min = -1.0, y_max = 1.0;
	#pragma omp parallel for default(none) private(x, y, cx, cy) shared(x_min, x_max, y_min, y_max, image) 
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			x = 0.0;
			y = 0.0;
			cx = x_min + (i / (float)(X - 1)) * (x_max - x_min);
			cy = y_min + (j / (float)(Y - 1)) * (y_max - y_min);
			int k;
			for (k = 0; x * x + y * y <= 4 && k < MAX_ITER; k++) {
				float x_tmp = x * x - y * y + cx;
				y = 2 * x * y + cy;
				x = x_tmp;
			}
			image[j][i] = (uint8_t)(k * 255 / MAX_ITER);
		}
	}
    return;
}

int main() {
    uint8_t image[Y][X];

	
	double startTime;
	double endTime;
	
	startTime = omp_get_wtime();
	
    calc_mandelbrot(image);

	endTime = omp_get_wtime();
	
	printf("time: %2.4f seconds\n", endTime-startTime);
    const int channel_nr = 1, stride_bytes = 0;
    stbi_write_png("mandelbrot_omp.png", X, Y, channel_nr, image, stride_bytes);
    return EXIT_SUCCESS;
}
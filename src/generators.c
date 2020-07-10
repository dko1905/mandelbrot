#include "generators.h"

int graph_terminal(int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max){
	f64 x, y;
	complex_f64 point, z;
	size_t steps;

	for(size_t num_y = 0; num_y < height; ++num_y){
		y = (f64)num_y / scale - (f64)height / 2. / scale + y_offset;

		for(size_t num_x = 0; num_x < width; ++num_x){
			x = (f64)num_x / scale - (f64)width / 2. / scale + x_offset;

			point = x + y * I;
			z = 0.0 + 0.0i;
			steps = 0;

			while(cabs(z) < 2.0 && steps < step_max){
				z = z * z + point;
				
				++steps;
			}

			if(steps < step_max){
				printf("#");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}
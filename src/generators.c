#include "generators.h"

int graph_terminal(graph_arguments_t args){
	f64 x, y;
	complex_f64 point, z;
	size_t steps;

	for(size_t num_y = 0; num_y < args.height; ++num_y){
		y = (f64)num_y / args.scale - (f64)args.height / 2. / args.scale + args.y_offset;

		for(size_t num_x = 0; num_x < args.width; ++num_x){
			x = (f64)num_x / args.scale - (f64)args.width / 2. / args.scale + args.x_offset;

			point = x + y * I;
			z = 0.0 + 0.0i;
			steps = 0;

			while(cabs(z) < 2.0 && steps < args.step_max){
				z = z * z + point;
				
				++steps;
			}

			if(steps < args.step_max){
				printf("#");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}
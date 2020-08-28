#include "generators.h"

pixel_t* raw_pixelat(pixel_t* buffer, int width, int height, int x, int y){
	return &buffer[width * y + x];
}

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

/*
Error codes:
-2	Failed to alocate memory
-1	Generic error
*/
int graph_png(char* filename, int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max, color_mode_t color_mode){
	bitmap_t image;
	int status;
	f64 x, y;
	complex_f64 point, z;
	size_t steps;
	pixel_t *pixel;

	/* Set to -1 when an error occures */
	status = 0;

	/* Setup image */
	image.width = width;
	image.height = height;

	/* Allocates whole image in one buffer, I dislike it but the example uses this */
	image.pixels = calloc(width * height, sizeof(pixel_t));

	if(!image.pixels){ /* Failed to allocate memory */
		return -2;
	}

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
				pixel = pixel_at(&image, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
				}
				else if(color_mode == HSV_1){
					char colors[3];
					HSVtoRGB((steps * 10) % 255, 1, 1, colors);
					pixel->red = colors[0];
					pixel->green = colors[1];
					pixel->blue = colors[2];
				}
			}
			else{
				pixel_t* pixel = pixel_at(&image, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
				else if(color_mode == HSV_1){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
			}
		}
		if(num_y % (height/100) == 0){
			printf("%1.f%%\n", ((f64)num_y / (f64)height) * 100);
		}
	}

	if (save_png_to_file (&image, filename)) {
		perror("Failed to write file");
		status = -1;
	}

	free (image.pixels);

	return status;
}

int graph_memory(pixel_t* buffer, int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max, color_mode_t color_mode){
	int status;
	f64 x, y;
	complex_f64 point, z;
	size_t steps;
	pixel_t *pixel;

	/* Set to -1 when an error occures */
	status = 0;

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
				pixel = raw_pixelat(buffer, width, height, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
				}
				else if(color_mode == HSV_1){
					char colors[3];
					HSVtoRGB((steps * 10) % 255, 1, 1, colors);
					pixel->red = colors[0];
					pixel->green = colors[1];
					pixel->blue = colors[2];
				}
			}
			else{
				pixel_t* pixel = raw_pixelat(buffer, width, height, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
				else if(color_mode == HSV_1){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
			}
		}
		if(height/100 != 0){
			if( num_y != 0 && num_y % (height/100) == 0){
			printf("%1.f%%\n", ((f64)num_y / (f64)height) * 100);
			}
		}
	}

	return status;
}

int graph_memory_fork(pixel_t* buffer, int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max, unsigned int th, color_mode_t color_mode){
	int status;
	f64 x, y;
	complex_f64 point, z;
	size_t steps;
	pixel_t *pixel;

	/* Set to -1 when an error occures */
	status = 0;

	int fpid = fork();

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
				pixel = raw_pixelat(buffer, width, height, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 255;
					pixel->green = 255;
					pixel->blue = 255;
				}
				else if(color_mode == HSV_1){
					char colors[3];
					HSVtoRGB((steps * 10) % 255, 1, 1, colors);
					pixel->red = colors[0];
					pixel->green = colors[1];
					pixel->blue = colors[2];
				}
			}
			else{
				pixel_t* pixel = raw_pixelat(buffer, width, height, num_x, num_y);
				if(color_mode == BLACKANDWHITE){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
				else if(color_mode == HSV_1){
					pixel->red = 0;
					pixel->green = 0;
					pixel->blue = 0;
				}
			}
		}
		if(height/100 != 0){
			if( num_y != 0 && num_y % (height/100) == 0){
			printf("%1.f%%\n", ((f64)num_y / (f64)height) * 100);
			}
		}
	}

	return status;
}
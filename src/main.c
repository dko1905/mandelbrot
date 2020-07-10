#include <stdio.h>
#include <string.h>

#include "pngtools.h"
#include "generators.h"
#include "license.h"

void print_license();

int main(int argc, char* argv[]){
	/* Check for min argument count */
	if(argc < 2){
		fprintf(stderr, "Invalid usage\n");
		return -1;
	}

	/* Arguments:
	n | gterm					| gpng
	1 - command/option
	2 - WIDTHxHEIGHT 	- filename
	3 - x offset			- WIDTHxHEIGHT
	4 - y offset			- x offset
	5 - scale					- y offset
	6 - iterations		- scale
	7 - none					- iterations
	8 - none					- Color mode
	*/

	switch(argv[1][0]){
		case 'l': /* License */
			print_license();
			break;
		case 'g': ;/* Generate */
			int width, height;
			f64 x_offset, y_offset, scale;
			size_t iterations;

			if(strcmp(argv[1], "gpng") == 0){ /* Generate png image */
				color_mode_t color_mode;
				char filename[FILENAME_MAX]; // FILENAME_MAX defined in std

				if(argc <= 8){
					fprintf(stderr, "Invalid usage\n");
					return 1;
				}

				strncpy(filename, argv[2], FILENAME_MAX);
				sscanf(argv[3], "%dx%d", &width, &height);
				x_offset = (f64)atof(argv[4]);
				y_offset = (f64)atof(argv[5]);
				scale = (f64)atof(argv[6]);
				sscanf(argv[7], "%llu", (unsigned long long*)&iterations);
				color_mode = (color_mode_t)atoi(argv[8]);

				int r = graph_png(filename, width, height, x_offset, y_offset, scale, iterations, color_mode);
				if(r < 0){
					if(r == -2){
						fprintf(stderr, "Failed to allocate memory\n");
						return -2;
					}
					else{
						perror("Unknown error");
						return -1;
					}
				}
			}
			if(strcmp(argv[1], "gterm") == 0){
				if(argc <= 5){
					fprintf(stderr, "Invalid usage\n");
					return 1;
				}

				sscanf(argv[2], "%dx%d", &width, &height);
				x_offset = (f64)atof(argv[3]);
				y_offset = (f64)atof(argv[4]);
				scale = (f64)atof(argv[5]);
				sscanf(argv[6], "%llu", (unsigned long long*)&iterations);

				graph_terminal(width, height, x_offset, y_offset, scale, iterations);
			}
			break;
	}
	
	return 0;

	/*
	graph_terminal( // Hate this giagantic list of arguments
		80,
		30,
		0.0,
		0.0,
		10.0,
		35
	);
	*/

	graph_png(
		"output2.png",
		1920 / 2,
		1080 / 2,
		2.0/3.0 - (486325.0/10000000.0),
		0.0,
		200.0,
		100000,
		HSV_1
	);
}

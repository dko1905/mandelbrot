#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "canvas.h"
#include "renderer.h"
#include "license.h"

#include "png.h"

int main(int argc, char *argv[]){
	/* Check for min argument count */
	if(argc < 2){
		fprintf(stderr, "Invalid usage\n");
		print_usage();
		return 1;
	}

  /* Arguments:
	n | gterm					| gpng          | gpngmt (UNIX ONLY)
	1 - command/option
	2 - WIDTHxHEIGHT 	- filename
	3 - x offset			- WIDTHxHEIGHT
	4 - y offset			- x offset
	5 - scale					- y offset
	6 - iterations		- scale
	7 - none					- iterations
	8 - none					- Color mode
  9 - none          - none          - thread count
	*/
switch(argv[1][0]){
		case 'l': /* License */
			print_license();
			break;
		case 'h':
			print_usage();
			break;
		case 'g': ;/* Generate */
			int width, height;
			double x_offset, y_offset, scale;
			size_t iterations;

			if(strcmp(argv[1], "gpng") == 0){ /* Generate png image */
				colormode_t colormode;
				char filename[FILENAME_MAX]; // FILENAME_MAX defined in std

				if(argc <= 8){
					fprintf(stderr, "Invalid usage\n");
					return 1;
				}

				strncpy(filename, argv[2], FILENAME_MAX);
				sscanf(argv[3], "%dx%d", &width, &height);
				x_offset = (double)atof(argv[4]);
				y_offset = (double)atof(argv[5]);
				scale = (double)atof(argv[6]);
				sscanf(argv[7], "%llu", (unsigned long long*)&iterations);
				colormode = (colormode_t)atoi(argv[8]);

        rendercanvas_t canvas = {
          width: width,
          height: height,
          buffer: malloc(sizeof(pixel_t) * width * height)
        };
        int r = rendertocanvas(&canvas, colormode, x_offset, y_offset, scale, iterations);
				if(r < 0){
          perror("Failed to render");
          return -1;
        }
        int r2 = savepng(&canvas, filename);
				if(r2 < 0){
					perror("Failed to save image");
          return -1;
				}
			}
			if(strcmp(argv[1], "gterm") == 0){
				if(argc <= 5){
					fprintf(stderr, "Invalid usage\n");
					return 1;
				}

				sscanf(argv[2], "%dx%d", &width, &height);
				x_offset = (double)atof(argv[3]);
				y_offset = (double)atof(argv[4]);
				scale = (double)atof(argv[5]);
				sscanf(argv[6], "%llu", (unsigned long long*)&iterations);

        rendercanvas_t canvas = {
          width: width,
          height: height,
          buffer: malloc(sizeof(pixel_t) * width * height)
        };
        int r = rendertocanvas(&canvas, BLACKANDWHITE, x_offset, y_offset, scale, iterations);
					if(r < 0){
          perror("Failed to render");
          return -1;
        }
        for(size_t y = 0; y < height; ++y){
          for (size_t x = 0; x < width; ++x)
          {
            if(pixel_at(&canvas, x, y)->red > 200){
              printf("#");
            } else{
              printf(" ");
            }
          }
          printf("\n");
        }
			}
      #ifdef __unix
			if(strcmp(argv[1], "gpngmt") == 0){ /* Generate png mutli threaded */
        colormode_t colormode;
				char filename[FILENAME_MAX]; // FILENAME_MAX defined in std

				if(argc <= 9){
					fprintf(stderr, "Invalid usage\n");
					return 1;
				}

				strncpy(filename, argv[2], FILENAME_MAX);
				sscanf(argv[3], "%dx%d", &width, &height);
				x_offset = (double)atof(argv[4]);
				y_offset = (double)atof(argv[5]);
				scale = (double)atof(argv[6]);
				sscanf(argv[7], "%llu", (unsigned long long*)&iterations);
				colormode = (colormode_t)atoi(argv[8]);
        size_t thread_count = atol(argv[9]);

        rendercanvas_t canvas = {
          width: width,
          height: height,
          buffer: malloc(sizeof(pixel_t) * width * height)
        };
        int r = rendertocanvas_multithread(&canvas, colormode, x_offset, y_offset, scale, iterations, thread_count);
				if(r < 0){
          perror("Failed to render");
          return -1;
        }
        int r2 = savepng(&canvas, filename);
				if(r2 < 0){
					perror("Failed to save image");
          return -1;
				}
      }
      #endif
      break;
		default:
			print_usage();
			break;
	}
	
	return 0;
}
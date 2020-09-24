#define _POSIX_C_SOURCE 200112L

// __STDC_NO_COMPLEX__ is c11, and should never be defined
#ifdef __STDC_NO_COMPLEX__
#error "Complex numbers not supported, because __STDC_NO_COMPLEX__ is defined"
#endif

#ifdef __unix__
#define PTHREAD_SUPPORTED 1
#else
#define PTHREAD_SUPPORTED 0
#endif

#include <complex.h>
// Check for complex number support
#ifndef _Complex_I
#error "Complex numbers not supported, because _Complex_I is not defined"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <png.h>
#include <stdint.h>
#include <string.h>

// Platform specific headers
#if PTHREAD_SUPPORTED == 1
#include <pthread.h>
#endif

// Error messages
static const char *err_invalid_usage = "Invalid usage: %s\n";
#if PTHREAD_SUPPORTED == 0
static const char *err_usage = "Usage: mandelbrot <output filename> <width> \
<height> <x offset> <y offset> <scale> <iterations>\n";
#else
static const char *err_usage = "Usage: mandelbrot <output filename> <width> \
<height> <x offset> <y offset> <scale> <iterations> <thread count>\n";
#endif

void hsv_to_rgb(uint_fast16_t H, double S, double V, uint8_t out[3]);
int render_png(
	const char *filename,
	unsigned int width,
	unsigned int height,
	double xoffset,
	double yoffset,
	double scale,
	size_t iterations,
	size_t thread_count
);

int main(int argc, char *argv[]){
	const char *filename = NULL;
	unsigned int width = 0, height = 0;
	double xoffset = 0., yoffset = 0., scale = 0.;
	size_t iterations = 0, thread_count = 0;
	if(argc < 9){
		fprintf(stderr, err_invalid_usage, "Not enough arguments");
		puts(err_usage);
		return 1;
	}

	// Set varibles
	filename = argv[1];
	width = atoll(argv[2]);
	height = atoll(argv[3]);
	xoffset = atof(argv[4]);
	yoffset = atof(argv[5]);
	scale = atof(argv[6]);
	// Check for invalid input
	if(filename == NULL || filename[0] == '\n' || filename[0] == '\0' || filename[0] == '\r'){
		fprintf(stderr, err_invalid_usage, "Filename is invalid");
		return 1;
	}
	if(width == 0){ // `==` because it's unsinged
		fprintf(stderr, err_invalid_usage, "Width is invalid");
		return 1;
	}
	if(height == 0){ // `==` because it's unsinged
		fprintf(stderr, err_invalid_usage, "Height is invalid");
		return 1;
	}
	if(sscanf(argv[7], "%zu", &iterations) < 1){
		fprintf(stderr, err_invalid_usage, "Iterations is invalid");
		return 1;
	} else if(iterations == 0){ // `==` because it's unsinged
		fprintf(stderr, err_invalid_usage, "Iterations must be over 0");
	}
	if(sscanf(argv[8], "%zu", &thread_count) < 1){
		fprintf(stderr, err_invalid_usage, "Thread count is invalid");
		return 1;
	} else if(thread_count == 0){ // `==` because it's unsinged
		fprintf(stderr, err_invalid_usage, "Thread count must be over 0");
		return 1;
	}
	return render_png(
		filename,
		width,
		height,
		xoffset,
		yoffset,
		scale,
		iterations,
		thread_count
	);
}

#if PTHREAD_SUPPORTED == 1
struct renderfuncparam{
	png_byte **row_parr; // Array of row pointers
	unsigned int width, height;
	png_structp png_ptr;
	double xoffset, yoffset;
	double scale;
	size_t iterations;
	int cpid; // Current pid
	int mpid; // Max pid
};

void *renderfunc(void *rawparam){
	struct renderfuncparam *param = (struct renderfuncparam *)rawparam;
	size_t y = 0, x = 0;
	unsigned int height = param->height;
	unsigned int width = param->width;
	double xoffset = param->xoffset;
	double yoffset = param->yoffset;
	size_t iterations = param->iterations;
	png_structp png_ptr = param->png_ptr;
	int cpid = param->cpid;
	int mpid = param->mpid;
	png_byte **row_parr = param->row_parr;
	double x_adj = 0, y_adj = 0;
	complex double point = 0, z = 0;
	size_t steps = 0;
	double scale = 1. / param->scale;
	png_byte *row;
	double yhso = 0; // Y, height, scale, offset 
	double xwso = 0; // X, width, scale, offset 

	for(y = 0 + cpid; y < height; y += mpid){
		row = png_calloc(png_ptr, sizeof(uint8_t) * width * 3); // 3 is RGB
		row_parr[y] = row;
	}

	// Performance tweaking
	yhso = (double)height * 0.5 * scale + yoffset;
	xwso = (double)width * 0.5 * scale + xoffset;
	for(y = 0 + cpid; y < height; y += mpid){
		row = row_parr[y]; // 3 is RGB
		y_adj = (double)y * scale - yhso;
		for(x = 0; x < width; ++x){
			x_adj = (double)x * scale - xwso;

			point = x_adj + y_adj * I;
			z = 0.;
			steps = 0;

			while(cabs(z) < 2.0 && steps < iterations){
				z = z * z + point;

				++steps;
			}

			if(steps < iterations)
				hsv_to_rgb((steps * 10) % 255, 1, 1, row);
			row += 3;
		}
	}
	
	return NULL;
}

#endif

int render_png(
	const char *filename,
	unsigned int width,
	unsigned int height,
	double xoffset,
	double yoffset,
	double scale,
	size_t iterations,
	size_t thread_count // Does not effect anything if it isn't supported
){
	FILE *file = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_byte **row_parr = NULL;
	size_t y = 0;
	int status = -1;
#if PTHREAD_SUPPORTED == 1
	size_t tc = 0;
	pthread_t *pthreads = NULL;
	struct renderfuncparam standardparam;
	struct renderfuncparam *customparam_arr = NULL;
	struct renderfuncparam *customparam = NULL;
	int cr = 0; // Create thread result
	int jr = 0; // Join thread result
#else
	double x_adj = 0, y_adj = 0;
	complex double point = 0, z = 0;
	size_t steps = 0, x = 0;
	double yhso = 0; // Y, height, scale, offset 
	double xwso = 0; // X, width, scale, offset
	scale = 1. / scale;
#endif

	// Open output file
	file = fopen(filename, "wb");
	if(file == NULL){
		goto fopen_failed;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr == NULL){
		goto png_create_write_struct_failed;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL){
		goto png_create_info_struct_failed;
	}

	// Setup error handling
	if (setjmp(png_jmpbuf(png_ptr))){
		goto png_failure;
	}

	// Setup attributes
	png_set_IHDR(
		png_ptr,
		info_ptr,
		width,
		height,
		8, // Color depth in bits, aka 1 byte
		PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);

	// Allocate array of rows
	row_parr = png_malloc(png_ptr, height * sizeof(png_byte *));
#if PTHREAD_SUPPORTED == 0
	// Performance tweaking
	yhso = (double)height * 0.5 * scale + yoffset;
	xwso = (double)width * 0.5 * scale + xoffset;
	// Go though rows
	for(y = 0; y < height; ++y){
		png_byte *row = png_calloc(png_ptr, sizeof(uint8_t) * width * 3); // 3 is RGB
		row_parr[y] = row;
		y_adj = (double)y * scale - yhso;
		for(x = 0; x < width; ++x){
			x_adj = (double)x * scale - xwso;

			point = x_adj + y_adj * I;
			z = 0. + 0.i;
			steps = 0;

			while(cabs(z) < 2.0 && steps < iterations){
				z = z * z + point;

				++steps;
			}

			if(steps < iterations)
				hsv_to_rgb((steps * 10) % 255, 1, 1, row);
			row += 3;
		}
	}
#else
	// Create default struct
	standardparam = (struct renderfuncparam){
		.row_parr = row_parr,
		.width = width,
		.height = height,
		.png_ptr = png_ptr,
		.xoffset = xoffset,
		.yoffset = yoffset,
		.scale = scale,
		.iterations = iterations,
		.cpid = 0,
		.mpid = 0
	};

	// Alocate array for pthread handles, and on for parameters.
	pthreads = malloc(sizeof(pthread_t) * thread_count);
	customparam_arr = (struct renderfuncparam*)malloc(sizeof(struct renderfuncparam) * thread_count);

	// Create pthreads
	for(tc = 0; tc < thread_count; ++tc){
		customparam = &customparam_arr[tc];
		memcpy(customparam, &standardparam, sizeof(struct renderfuncparam));

		customparam->cpid = tc;
		customparam->mpid = thread_count;

		cr = pthread_create(&pthreads[tc], NULL, renderfunc, (void *)customparam);
		if(cr < 0){
			perror("Failed to create pthread, exiting");
			goto pthread_failure;
		}
	}

	for(tc = 0; tc < thread_count; ++tc){
		jr = pthread_join(pthreads[tc], NULL);
		if(jr < 0){
			perror("Failed to join pthread, continuing");
		}
	}

#endif

	// Write image to file
	png_init_io(png_ptr, file);
	png_set_rows(png_ptr, info_ptr, row_parr);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	// It succeded so set status to 0
	status = 0;

	// Cleanup
	for (y = 0; y < height; ++y)
	{
		png_free(png_ptr, row_parr[y]);
	}
	png_free(png_ptr, row_parr);

	// Clean threads
#if PTHREAD_SUPPORTED == 1
pthread_failure:
	free(pthreads);
	free(customparam_arr);
#endif

	// Clean other stuff
png_failure:
png_create_info_struct_failed:
	png_destroy_write_struct(&png_ptr, &info_ptr);
png_create_write_struct_failed:
	fclose(file);
fopen_failed:
	return status;
}

inline void hsv_to_rgb(uint_fast16_t H, double S, double V, uint8_t out[3]){
	double C = S * V;
	double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	else if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	else if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	else if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	else if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;	
	}
	
	out[0] = (Rs + m) * 255;
	out[1] = (Gs + m) * 255;
	out[2] = (Bs + m) * 255;
}

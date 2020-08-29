#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <png.h>
#include <stdint.h>
#include <strings.h>

#ifdef __unix__
#define PTHREAD_SUPPORTED 0
#else
#define PTHREAD_SUPPORTED 1
#endif

#if PTHREAD_SUPPORTED == 1
#include <pthread.h>
#endif

void HSVtoRGB(int H, double S, double V, uint8_t out[3]);
int render_png(
	const char *filepath,
	unsigned int width,
	unsigned int height,
	double xoffset,
	double yoffset,
	double scale,
	size_t iterations,
	size_t thread_count
);

int main(int argc, char *argv[]){
	return render_png(
		"out.png",
		1920,
		1080,
		0,
		0,
		400,
		100,
		8
	);

  return 0;
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
	double scale = param->scale;
	png_byte *row;
	
	printf("Before alocation\n");

	for(y = 0 + cpid; y < height; y += mpid){
		row = png_calloc(png_ptr, sizeof(uint8_t) * width * 3); // 3 is RGB
		row_parr[y] = row;
	}

	printf("After alocation\n");

	for(y = 0 + cpid; y < height; y += mpid){
		row = row_parr[y]; // 3 is RGB
		y_adj = (double)y / scale - (double)height / 2. / scale + yoffset;
		for(x = 0; x < width; ++x){
			x_adj = (double)x / scale - (double)width / 2. / scale + xoffset;

			point = x_adj + y_adj * I;
			z = 0. + 0.i;
			steps = 0;

			while(cabs(z) < 2.0 && steps < iterations){
        z = z * z + point;

        ++steps;
      }

			if(steps < iterations)
				HSVtoRGB((steps * 10) % 255, 1, 1, row);
			row += 3;
		}
	}

	printf("After calculation\n");

	return NULL;
}

#endif

int render_png(
	const char *filepath,
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
	pthread_t *pthreads;
	#else
	double x_adj = 0, y_adj = 0;
	complex double point = 0, z = 0;
  size_t steps = 0;
	size_t x = 0;
	#endif

	// Open output file
  file = fopen(filepath, "wb");
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
	// Go though rows
	for(y = 0; y < height; ++y){
		png_byte *row = png_calloc(png_ptr, sizeof(uint8_t) * width * 3); // 3 is RGB
		row_parr[y] = row;
		y_adj = (double)y / scale - (double)height / 2. / scale + yoffset;
		for(x = 0; x < width; ++x){
			x_adj = (double)x / scale - (double)width / 2. / scale + xoffset;

			point = x_adj + y_adj * I;
			z = 0. + 0.i;
			steps = 0;

			while(cabs(z) < 2.0 && steps < iterations){
        z = z * z + point;

        ++steps;
      }

			if(steps < iterations)
				HSVtoRGB((steps * 10) % 255, 1, 1, row);
			row += 3;
		}
	}
#else
	// Create default struct
	struct renderfuncparam standardparam = {
		row_parr: row_parr,
		width: width,
		height: height,
		png_ptr: png_ptr,
		xoffset: xoffset,
		yoffset: yoffset,
		scale: scale,
		iterations: iterations,
		cpid: 0,
		mpid: 0
	};

	// Alocate array for pthread handles, and on for parameters.
	pthreads = malloc(sizeof(pthread_t) * thread_count);
	struct renderfuncparam *customparam_arr = malloc(sizeof(struct renderfuncparam) * thread_count);

	// Create pthreads
	for(size_t tc = 0; tc < thread_count; ++tc){
    struct renderfuncparam *customparam = &customparam_arr[tc];
    bcopy(&standardparam, customparam, sizeof(struct renderfuncparam));

    customparam->cpid = tc;
    customparam->mpid = thread_count;

    int cr = pthread_create(&pthreads[tc], NULL, renderfunc, (void *)customparam);
    if(cr < 0){
      perror("Failed to create pthread, exiting");
      goto pthread_failure;
    }
  }

  for(size_t tc = 0; tc < thread_count; ++tc){
    int jr = pthread_join(pthreads[tc], NULL);
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

inline void HSVtoRGB(int H, double S, double V, uint8_t out[3]){
	double C = S * V;
	double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H >= 0 && H < 60) {
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
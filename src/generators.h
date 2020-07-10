#pragma once

#include <stdio.h>
#include <complex.h>

#include "pngtools.h"
#include "hsv.h"

typedef double f64;
typedef _Complex double complex_f64;

typedef enum {
	BLACKANDWHITE = 0,
	HSV_1 = 1
} color_mode_t;

int graph_terminal(int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max);

int graph_png(char* filename, int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max, color_mode_t color_mode);
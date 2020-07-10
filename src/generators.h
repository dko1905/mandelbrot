#pragma once

#include <stdio.h>
#include <complex.h>

#include "pngtools.h"

typedef double f64;
typedef _Complex double complex_f64;

typedef struct {
	int width, height;
	f64 x_offset, y_offset, scale;
	size_t step_max;
	bitmap_t* bitmap;
} graph_arguments_t;

int graph_terminal(graph_arguments_t args);
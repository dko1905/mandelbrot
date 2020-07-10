#pragma once

#include <stdio.h>
#include <complex.h>

#include "pngtools.h"

typedef double f64;
typedef _Complex double complex_f64;

int graph_terminal(int width, int height, f64 x_offset, f64 y_offset, f64 scale, size_t step_max);
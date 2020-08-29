#ifndef RENDERER_H
#define RENDERER_H

#include <complex.h>
#include "colormode.h"
#include "canvas.h"

#ifdef __unix__
#include <unistd.h>
#include <pthread.h>
#endif

int rendertocanvas(rendercanvas_t *canvas, colormode_t colormode, double x_offset, double y_offset, double scale, size_t step_max);

#ifdef __unix__
int rendertocanvas_multithread(rendercanvas_t *canvas, colormode_t colormode, double x_offset, double y_offset, double scale, size_t step_max, size_t thread_n);
#endif

#endif
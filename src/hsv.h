#ifndef HSV_H
#define HSV_H

#include <math.h>
#include <stdlib.h>
#include "canvas.h"

/*
 * All credit goes to kuathadianto for the gist.
 * https://gist.github.com/kuathadianto/200148f53616cbd226d993b400214a7f
 */
void HSVtoRGB(int H, double S, double V, pixel_t *pixel);

#endif
#ifndef CANVAS_H
#define CANVAS_H

#include "rendercanvas.h"
#include "pixel.h"

#include <stdint.h>

pixel_t *pixel_at(const rendercanvas_t *canvas, const unsigned int x, const unsigned int y);

#endif
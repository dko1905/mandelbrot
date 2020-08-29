#ifndef RENDERCANVAS_H
#define RENDERCANVAS_H

#include <stdint.h>
#include "pixel.h"

typedef struct rendercanvas {
  uint32_t width, height;
  pixel_t *buffer;
} rendercanvas_t;

#endif
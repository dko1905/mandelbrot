#include <stdint.h>

#include "canvas.h"

inline pixel_t *pixel_at(const rendercanvas_t *canvas, const unsigned int x, const unsigned int y) {
  return canvas->buffer + canvas->width * y + x;
}
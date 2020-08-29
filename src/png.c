#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "png.h"
#include "canvas.h"

int savepng(const rendercanvas_t *canvas, const char *filepath)
{
  FILE *fp;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  size_t x, y;
  png_byte **row_pointers = NULL;

  int status = -1;

  int pixel_size = 3;
  int depth = 8;

  fp = fopen(filepath, "wb");
  if (!fp)
  {
    goto fopen_failed;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL)
  {
    goto png_create_write_struct_failed;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL)
  {
    goto png_create_info_struct_failed;
  }

  /* Set up error handling. */

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    goto png_failure;
  }

  /* Setup image attributes */

  png_set_IHDR(
      png_ptr,
      info_ptr,
      canvas->width,
      canvas->height,
      depth,
      PNG_COLOR_TYPE_RGB,
      PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_DEFAULT,
      PNG_FILTER_TYPE_DEFAULT);

  row_pointers = png_malloc(png_ptr, canvas->height * sizeof(png_byte *));
  for (y = 0; y < canvas->height; y++)
  {
    png_byte *row =
        png_malloc(png_ptr, sizeof(uint8_t) * canvas->width * pixel_size);
    row_pointers[y] = row;
    for (x = 0; x < canvas->width; x++)
    {
      pixel_t *pixel = pixel_at(canvas, x, y);
      *row++ = pixel->red;
      *row++ = pixel->green;
      *row++ = pixel->blue;
    }
  }

  /* Write the image data to "fp". */

  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  /* The routine has successfully written the file, so we set
    "status" to a value which indicates success. */

  status = 0;

  for (y = 0; y < canvas->height; y++)
  {
    png_free(png_ptr, row_pointers[y]);
  }
  png_free(png_ptr, row_pointers);

png_failure:
png_create_info_struct_failed:
  png_destroy_write_struct(&png_ptr, &info_ptr);
png_create_write_struct_failed:
  fclose(fp);
fopen_failed:
  return status;
}
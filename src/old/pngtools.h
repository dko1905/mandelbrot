#pragma once

#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // For fixed size integers

/* A coloured pixel. */

typedef struct
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_t;

/* A picture. */

typedef struct
{
	pixel_t *pixels;
	size_t width;
	size_t height;
} bitmap_t;

pixel_t *pixel_at(bitmap_t *bitmap, int x, int y);

int save_png_to_file(bitmap_t *bitmap, const char *path);
#include <stdio.h>

#include "pngtools.h"
#include "generators.h"

void print_license();

int main(int argc, char* argv[])
{
	if(argc > 1 && argv[1][0] == 'l'){
		print_license();
		return 0;
	}

	bitmap_t fruit;
	int x;
	int y;
	int status;

	status = 0;

	/* Create an image. */

	fruit.width = 1920;
	fruit.height = 1080;

	fruit.pixels = calloc(fruit.width * fruit.height, sizeof(pixel_t));

	if (!fruit.pixels)
	{
		return -1;
	}

	for (y = 0; y < fruit.height; y++)
	{
		for (x = 0; x < fruit.width; x++)
		{
			pixel_t *pixel = pixel_at(&fruit, x, y);
			pixel->red = x % 255;
			pixel->green = y % 255;
			pixel->blue = 200;
		}
	}

	/* Write the image to a file 'fruit.png'. */

	if (save_png_to_file(&fruit, "fruit.png"))
	{
		fprintf(stderr, "Error writing file.\n");
		status = -1;
	}

	free(fruit.pixels);

	return status;
}

void print_license(){
	printf("Copyright (c) 2020, Daniel Florescu \nAll rights reserved. \n\nRedistribution and use in source and binary forms, with or without \nmodification, are permitted provided that the following conditions are met: \n\n * Redistributions of source code must retain the above copyright notice, \n   this list of conditions and the following disclaimer. \n * Redistributions in binary form must reproduce the above copyright \n   notice, this list of conditions and the following disclaimer in the \n   documentation and/or other materials provided with the distribution. \n\nTHIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS\'\' AND ANY \nEXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED \nWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE \nDISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY \nDIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES \n(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR \nSERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER \nCAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT \nLIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY \nOUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH \nDAMAGE. \n");
}
#include <stdio.h>

#include "pngtools.h"
#include "generators.h"
#include "license.h"

void print_license();

int main(int argc, char* argv[]){
	if(argc > 1 && argv[1][0] == 'l'){
		print_license();
		return 0;
	}

	/*
	graph_terminal( // Hate this giagantic list of arguments
		80,
		30,
		0.0,
		0.0,
		10.0,
		35
	);*/

	graph_png(
		"output.png",
		1920,
		1080,
		0.0,
		0.0,
		400.0,
		10000,
		BLACKANDWHITE
	);
}
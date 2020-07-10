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
		"output2.png",
		1920 / 2,
		1080 / 2,
		2.0/3.0 - (486325.0/10000000.0),
		0.0,
		200.0,
		100000,
		HSV_1
	);
}

#include <stdio.h>

#include "pngtools.h"
#include "generators.h"
#include "license.h"

void print_license();

int main(int argc, char* argv[]){
	/* Check for min argument count */
	if(argc < 2){
		fprintf(stderr, "Invalid usage\n");
		return -1;
	}

	/* Arguments:
	1 - command/option
	2 - WIDTHxHEIGHT
	3 - x offset
	4 - y offset

	*/

	switch(argv[1][0]){
		case 'l':
			print_license();
			break;
		case 'p':
			break;
	}
	
	return 0;

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

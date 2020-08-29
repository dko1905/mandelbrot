#include "hsv.h"
#include "canvas.h"

/*
 * All credit goes to kuathadianto for the gist.
 * https://gist.github.com/kuathadianto/200148f53616cbd226d993b400214a7f
 */
void HSVtoRGB(int H, double S, double V, pixel_t *pixel) {
	double C = S * V;
	double X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if(H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;	
	}
	else if(H >= 60 && H < 120) {	
		Rs = X;
		Gs = C;
		Bs = 0;	
	}
	else if(H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;	
	}
	else if(H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;	
	}
	else if(H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;	
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;	
	}
	
	pixel->red = (Rs + m) * 255;
	pixel->green = (Gs + m) * 255;
	pixel->blue = (Bs + m) * 255;
}
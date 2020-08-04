cc=cc
cflags=-Wall -std=c99 -lm -lpng -lz 

mandelbrot: main.o pngtools.o generators.o hsv.o
	$(cc) main.o pngtools.o generators.o hsv.o -o build/mandelbrot $(cflags)
main.o: src/main.c
	$(cc) -c src/main.c $(cflags)
pngtools.o: src/pngtools.c
	$(cc) -c src/pngtools.c $(cflags) 
generators.o: src/generators.c
	$(cc) -c src/generators.c $(cflags)
hsv.o: src/hsv.c
	$(cc) -c src/hsv.c $(cflags)

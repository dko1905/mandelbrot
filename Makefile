cc=cc
cflags=-Wall -std=c99 -lm -lpng -lz 

mandelbrot: main.o
	$(cc) main.o  -o build/mandelbrot $(cflags)
main.o: src/main.c
	$(cc) -c src/main.c $(cflags)
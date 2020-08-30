CC = cc
CFLAGS = -Wall -std=c99 -O3 -ffast-math
LDFLAGS = -lm -lpng -lz -lpthread

CFLAGS += $(INCLUDES)

mandelbrot: main.o
	$(CC) main.o -o build/mandelbrot $(LDFLAGS)
main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)

clean:
	rm *.o
	rm build/*
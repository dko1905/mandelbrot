CC = cc
CFLAGS = -Wall -std=c99 -lm -lpng -lz -lpthread

CFLAGS += $(INCLUDES)

mandelbrot: main.o
	$(CC) main.o -o build/mandelbrot $(CFLAGS)
main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)

clean:
	rm *.o
	rm build/*
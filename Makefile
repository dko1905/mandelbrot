CC = cc
CFLAGS = -Wall -std=c99 -lm -lpng -lz -lpthread

CFLAGS += $(INCLUDES)

mandelbrot: main.o renderer.o hsv.o png.o canvas.o
	$(CC) main.o hsv.o renderer.o png.o canvas.o -o build/mandelbrot $(CFLAGS)
main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)
renderer.o: src/renderer.c
	$(CC) -c src/renderer.c $(CFLAGS)
hsv.o: src/hsv.c
	$(CC) -c src/hsv.c $(CFLAGS)
png.o: src/png.c
	$(CC) -c src/png.c $(CFLAGS)
canvas.o: src/canvas.c
	$(CC) -c src/canvas.c $(CFLAGS)

clean:
	rm *.o
	rm build/*
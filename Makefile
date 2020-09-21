.POSIX:

MYCFLAGS = -std=c99 -O3 -ffast-math -Wall -Wextra -Wno-builtin-declaration-mismatch $(CFLAGS)
MYLDFLAGS = -lm -lpng -lz -pthread $(LDFLAGS)
OBJECTS = main.o

all: mandelbrot
mandelbrot: $(OBJECTS)
	$(CC) $(OBJECTS) -o mandelbrot $(MYLDFLAGS)
.c.o:
	$(CC) $(MYCFLAGS) -c $<

.PHONY: clean
clean:
	rm -f xorcryptor $(OBJECTS)
	rm -f *.o
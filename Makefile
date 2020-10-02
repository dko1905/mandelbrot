.POSIX:

PKG_CONFIG = pkg-config

MYCFLAGS = -std=c99 -ffast-math -Wall -Wextra -pedantic $(CFLAGS)
MYLDFLAGS = $(LDFLAGS) -lm -pthread \
	`$(PKG_CONFIG) --libs libpng`

OBJECTS = main.o

all: mandelbrot
mandelbrot: $(OBJECTS)
	$(CC) $(OBJECTS) -o mandelbrot $(MYLDFLAGS)
.c.o:
	$(CC) $(MYCFLAGS) -c $<

.PHONY: clean
clean:
	rm -f mandelbrot $(OBJECTS)
	rm -f *.o

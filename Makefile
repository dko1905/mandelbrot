.POSIX:

include config.mk

OBJECTS = main.o

all: options mandelbrot

options:
	@echo Mandelbrot build options:
	@echo "CFLAGS  = $(MYCFLAGS)"
	@echo "LDFLAGS = $(MYLDFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(MYCFLAGS) -c $<

mandelbrot: $(OBJECTS)
	$(CC) $(OBJECTS) -o mandelbrot $(MYLDFLAGS)

clean:
	rm -f mandelbrot $(OBJECTS)

.PHONY: all options clean

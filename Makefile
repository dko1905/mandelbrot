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

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f mandelbrot $(DESTDIR)$(PREFIX)/bin
	chmod +x $(DESTDIR)$(PREFIX)/bin/mandelbrot

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/mandelbrot

.PHONY: all options clean install uninstall

# Mandelbrot version
VERSION = 0.1.2
VERBOSE = 1

# Customize to fit your system
PKG_CONFIG = pkg-config

# Includes and libs
INCS = `$(PKG_CONFIG) --cflags libpng` \
       `$(PKG_CONFIG) --cflags zlib`
LIBS = -lm -pthread \
       `$(PKG_CONFIG) --libs libpng` \
       `$(PKG_CONFIG) --libs zlib`

# Flags
MYCPPFLAGS = `if ! [ -z "$(PTHREAD_SUPPORTED)" ]; then echo -n -DPTHREAD_SUPPORTED=$(PTHREAD_SUPPORTED); fi` \
             -DVERBOSE=\"$(VERBOSE)\" \
             -DVERSION=\"$(VERSION)\" # My Preprocessor
MYCFLAGS = -std=c99 -Wall -Wextra -pedantic \
           $(INCS) $(MYCPPFLAGS) $(CPPFLAGS) $(CFLAGS) # My C-flags
MYLDFLAGS = $(LIBS) $(LDFLAGS) # My LD flags


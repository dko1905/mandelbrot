# Mandelbrot version
VERSION = 0.1.3
VERBOSE = 1
#USE_PTHREAD = 0 # Force pthread usage

# Customize to fit your system
PKG_CONFIG = pkg-config

# Paths
PREFIX = /usr/local

# Includes and libs
INCS = `$(PKG_CONFIG) --cflags libpng` \
       `$(PKG_CONFIG) --cflags zlib`
LIBS = -lm -pthread \
       `$(PKG_CONFIG) --libs libpng` \
       `$(PKG_CONFIG) --libs zlib`

# Flags
MYCPPFLAGS = `if [ ! -z $(USE_PTHREAD) ]; then echo -n -DUSE_PTHREAD=$(USE_PTHREAD); fi` \
             -DVERBOSE=$(VERBOSE) \
             -DVERSION=\"$(VERSION)\" # My Preprocessor
MYCFLAGS = -std=c99 -Wall -Wextra -pedantic \
           $(INCS) $(MYCPPFLAGS) $(CPPFLAGS) $(CFLAGS) # My C-flags
MYLDFLAGS = $(LIBS) $(LDFLAGS) # My LD flags

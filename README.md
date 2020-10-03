# Mandelbrot Generator
![C CI](https://github.com/Dko1905/mandelbrot/workflows/C%20CI/badge.svg)<br/>
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
This program has libpng and zlib as dependencies. Here is a table of dependency names on different systems:

| Distro       | libpng       | zlib       |
|--------------|--------------|------------|
| Ubuntu 20.04 | libpng-dev   | zlib1g-dev |
| Void Linux   | libpng-devel | zlib-devel |
| Fedora       | libpng-devel | zlib-devel |

After installing all dependencies, you just run `make`.

## Usage
To get usage:
```
$ ./mandelbrot
Invalid usage: Not enough arguments
Version: 0.1.1
Usage: mandelbrot <output filename> <width> <height> <x offset> <y offset> <scale> <iterations> <thread count (not used)>
```

## Configuration
### `config.mk` options (makefile variables):
`VERBOSE`: Set this to 1 if you want verbose info when running the program.  
`VERSION`: Set this to the version you want displayed in the program, any string is acceptable.  
`PKG_CONFIG`: Set this to the path or name of your preferred pkg-config.
### Compiler options (enviroment variables):
`PTHREAD_SUPPORTED`: Set this to 1 if you want to force pthread usage.  
`CC`: Set this to change the compiler  
`CPPFLAGS`: C preprocessor flags  
`CFLAGS`: C compiler flags  
`LDFLAGS`: Linker flags  

## Examples
It's quite hard to test speed, so I'll just say it's fast.

Here is a HD render
![image of mandelbrot](doc_image.png)

## License
[MIT](LICENSE)


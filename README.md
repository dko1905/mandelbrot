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
Usage: mandelbrot <output filename> <width> <height> <x offset> <y offset> <scale> <iterations> (<thread count>)
```
`<thread count>` only works if it is compiled on unix, or if the `__unix__` flag is set.
## Examples
It's quite hard to test speed, so I'll just say it's fast.

Here is a HD render
![image of mandelbrot](doc_image.png)

## License
[MIT](LICENSE)

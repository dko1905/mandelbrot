# Mandelbrot Generator
![C CI](https://github.com/Dko1905/mandelbrot/workflows/C%20CI/badge.svg)<br/>
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
This program has libpng and zlib as dependencies. Here is a table:

| Distro       | libpng       | zlib       |
|--------------|--------------|------------|
| Ubuntu 20.04 | libpng-dev   | zlib1g-dev |
| Void Linux   | libpng-devel | zlib-devel |
| Fedora       | libpng-devel | zlib-devel |

You also need make and a compiler. To compile the program, you run the following command.
`$ mkdir -p build && make`
The command will compile into the build folder.

## Usage
This is not currently implemented.
```
./mandelbrot 
```
## Examples
It's quite hard to test speed, so I'll just say it's fast.

Here is a HD render
![image of mandelbrot](doc_image.png)

## License
[MIT](LICENSE)

# Mandelbrot Generator
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
This program has libpng and zlib as dependencies. Here is a table:

| Distro       | libpng       | zlib       |
|--------------|--------------|------------|
| Ubuntu 20.04 | libpng-dev   | zlib1g-dev |
| Void Linux   | libpng-devel | zlib-devel |

You also need make and a compiler. To compile the program, you run the following command.
`$ mkdir -p build && make`
The command will compile into the build folder.

## Usage
./mandelbrot <option> <args> <br/>
options: <br/>
gpng <filename> <WIDTHxHEIGHT> <x_offset> <y_offset> <scale (400 for HD)> <iterations> <color mode 0-1> <br/>
gterm <WIDTHxHEIGHT> <x_offset> <y_offset> <scale (400 for HD)> <iterations> <br/>
gpngmt <WIDTHxHEIGHT> <x_offset> <y_offset> <scale (400 for HD)> <iterations> <thread count>

gpngmt is only avaiable on unix!
## Examples
35 iterations: 0.55s
10000 iterations: 41.67s

Here is the 35 iterations example:
![image of mandelbrot](doc_image.png)

## License
[BSD 2 Clause](LICENSE)

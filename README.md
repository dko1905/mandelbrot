# Mandelbrot Generator
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
These settings were used: -O3 on gcc, and 400 scale for HD. <br/>
8K (15360x8640), 100 iterations, 4 threads: 11,9s <br/>
HD (1920x1080), 100 iterations, 1 thread: 0.5s <br/>

Here is the HD example
![image of mandelbrot](doc_image.png)

## License
[BSD 2 Clause](LICENSE)

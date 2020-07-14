# Mandelbrot Generator
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
You need to have cmake installed, and vs on win, and make/gcc on *nix.
**Warning** If your system doesn't have libpng-devel installed, you should git clone with `--recursive` option.
### *nix
This should compile it to the dist folder.
```
$ cmake .
$ make
```
### Windows
You need to vs and cmake installed, and you need to open cmd/powershell with vs tools. <br/>**I have not tested this.**
```
$ cmake "NMake Makefiles" .
$ nmake .
```

**Using mingw**

## Usage
./mandelbrot <option> <args> <br/>
options: <br/>
gpng <filename> <WIDTHxHEIGHT> <x_offset> <y_offset> <scale (400 for HD)> <iterations> <color mode 0-1> <br/>
gterm <WIDTHxHEIGHT> <x_offset> <y_offset> <scale (400 for HD)> <iterations> <br/>

## Examples
35 iterations: 0.55s
10000 iterations: 41.67s

Here is the 35 iterations example:
![image of mandelbrot](doc_image.png)

## License
[BSD 2 Clause](LICENSE)

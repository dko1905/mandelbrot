# Mandelbrot Generator
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
You need to have cmake installed, and vs on win, and make/gcc on *nix.
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

## License
[BSD 2 Clause](LICENSE)
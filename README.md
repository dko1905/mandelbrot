# Mandelbrot Generator
![C CI](https://github.com/Dko1905/mandelbrot/workflows/C%20CI/badge.svg)<br/>
This is a mandelbrot generator written in c using libpng with zlib to create png images.

## Compiling
This program has libpng and zlib as dependencies. Here is a table of dependency names on different systems:
Remember that pkg-config, make and a c99 compatible compiler (gcc, tcc...) are required to compile.

| Distro       | libpng       | zlib       |
|--------------|--------------|------------|
| Ubuntu 20.04 | libpng-dev   | zlib1g-dev |
| Void Linux   | libpng-devel | zlib-devel |
| Fedora       | libpng-devel | zlib-devel |

After installing all dependencies, you just run `make`.

## Installing and uninstalling
Remember to have the right permissions, by using `sudo` or running as root.
Install: `make install`
Uninstall: `make uninstall`

By default it installs the binary to `/usr/local/bin`, you can change this under [Configuration](#Configuration).

## Usage
To get the usage run the program without any parameters.
To get the version and license run the program with `-v`.

## Configuration
### `config.mk` options (makefile variables):
| Name       | Default value | Description                                                                          |
|------------|---------------|--------------------------------------------------------------------------------------|
| VERBOSE    | 1             | This changes the verboseness of the program.                                         |
| VERSION    | <version>     | This changes the version printed when running the program. Any string is acceptable. |
| PKG\_CONFIG| pkg-config    | This changes the binary that is used for pkg-config.                                 |
| PREFIX     | /usr/local    | This changes where the binary is installed to. ( /usr/local/bin )                    |
### Compiler options (enviroment variables):
| Name              | Default value   | Description                                              |
|-------------------|-----------------|----------------------------------------------------------|
| PTHREAD_SUPPORTED | Depends on OS   | You can set this to force using one or multiple threads. |
| CC                | Depends on make | You can set this to force a specific compiler.           |
| CPPFLAGS          | Empty           | C preprocessor flags                                     |
| CFLAGS            | Depends on make | C compiler flags                                         |
| LDFLAGS           | Empty           | Linker flags                                             |

## Examples
1920x1080, 400 zoom, 4000 iterations: <br/>
![image of mandelbrot](doc_image.png)

## License
[BSD-2-Clause](LICENSE)

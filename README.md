# cpp-raytracer: a simple C++ raytracer

This program is an object-oriented Ray Tracer written in C++ with SDL2. It can parse simple scenes made of spheres, planes, and point lights from a file and render them, with associated colors in ambient, diffuse, and specular, as well as Blinn-Phong shading.

## Installation

```bash
$ git clone https://github.com/nsilvestri/cpp-raytracer
$ cd cpp-raytracer
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execution
```bash
$ ./prog03 scene_file output_file
```
#### Example
```bash
$ ./prog03 ../scenes/myscene.ppm render.ppm
```

## Usage

While running the program:
* `RETURN` writes the current render to the file specified at the command line.

## Testing

There are some Catch2 tests in the `test/` directory. Compile them with the makefile provided. Unit tests are not complete, at all, but they are there.

## Notes

Code has been tested on cambridge. Tested to work on all scenes in the `scenes/` directory.

I started doxygen/Javadoc style comments for some of it. To be updated later.

#### Known Bugs

Occasional self-intersection issue. Mitigate mostly with a self-intersection offset, but that itself has some side effects.
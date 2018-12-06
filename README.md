# cpp-raytracer: a simple C++ ray tracer

This program is an object-oriented ray tracer written in C++ with SDL2. It can parse simple scenes made of spheres, planes, and point lights from a file and render them with Blinn-Phong shading.

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
$ ./raytrace scene_file output_file
```
#### Example
```bash
$ ./raytrace ../scenes/myscene.ppm render.ppm
```

## Usage

While running the program:
* `RETURN` writes the current render to the file specified at the command line.

## Testing

There are some Catch2 tests in the `test/` directory. Compile them with the makefile provided. Unit tests are not complete, at all, but they are there.

## Notes

I started doxygen/Javadoc style comments for some of it. To be updated later.

#### Known Bugs

Occasional self-intersection issue. Mitigate mostly with a self-intersection offset, but that itself has some side effects.
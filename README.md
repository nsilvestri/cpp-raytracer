# CSC 433 prog03 -- Simple Ray Tracer

This program is an object-oriented Ray Tracer written in C++ with SDL2. It can parse simple scenes made of spheres, planes, and point lights from a file and render them, with associated colors in ambient, diffuse, and specular, as well as Blinn-Phong shading.

## Installation

```bash
$ git clone https://github.com/UA-CSC433-Fall2018/asgmt03-nsilvestri
$ cd asgmt03-nsilvestri
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

Shadows are kind of crappy, and there's some weird coloration issues with lights and whatnot. I played around with it for a long, long time and never was able to get it working without messing up something else. The ray tracing part is set to be overhauled.
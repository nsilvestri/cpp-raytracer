# cpp-raytracer: a simple C++ ray tracer

This program is an object-oriented ray tracer written in C++ with SDL2. It can parse simple scenes made of spheres, planes, and point lights from a file and render them with Blinn-Phong shading.

![3spheres433.png](https://github.com/nsilvestri/cpp-raytracer/blob/master/outputs/3spheres433.png "outputs/3spheres433.png")

## Features

- [x] Spheres and Planes
- [ ] Meshes
- [x] Point lights
- [ ] Area lights
- [x] Shadows
- [x] Blinn-Phong shading
- [ ] Mirror reflections
- [ ] Dielectrics
- [ ] Multi-core rendering
- [ ] Real-time rendering

## Installation

```bash
git clone https://github.com/nsilvestri/cpp-raytracer
cd cpp-raytracer
mkdir build
cd build
cmake ..
make
```

SDL2 is required to run this program and display the images.

### Ubuntu (apt)

`sudo apt install libsdl2-dev`

#### WSL Ubuntu(s)

In order to display the window `sudo apt install x11-apps`, and get an X server such as Xming running. In order to display to the X server, do `export DISPLAY=localhost:0.0`. After that the image should display in the X server window.

### Arch (pacman)

`sudo pacman -S sdl2`

## Execution

```bash
./raytrace scene_file output_file
```

### Example

```bash
./raytrace ../scenes/myscene.ppm render.ppm
```

## Usage

While running the program:

- `RETURN` writes the current render to the file specified at the command line.

## Testing

There are some Catch2 tests in the `test/` directory. Compile them with the makefile provided. Unit tests are not complete, at all, but they are there.

## Notes

I started doxygen/Javadoc style comments for some of it. To be updated later.

### Known Bugs

Occasional self-intersection issue. Mitigate mostly with a self-intersection offset, but that itself has some side effects.

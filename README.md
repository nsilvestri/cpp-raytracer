# cpp-raytracer: a simple C++ ray tracer

This program is an object-oriented ray tracer written in C++. It can parse simple scenes made of spheres, planes, and point lights from a file and render them with Blinn-Phong shading.

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

## Execution

```bash
./raytrace scene_file output_file
```

### Example

```bash
./raytrace ../scenes/myscene.ppm render.ppm
```

## Testing

There are some Catch2 tests in the `test/` directory. Compile them with the makefile provided. Unit tests are not complete, at all, but they are there.

## Notes

I started doxygen/Javadoc style comments for some of it. To be updated later.

### Known Bugs

Occasional self-intersection issue. Mitigate mostly with a self-intersection offset, but that itself has some side effects.

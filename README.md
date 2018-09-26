# CSC 433 prog02 -- Simple Image Editor

This program can display and edit the gain, bias, and gamma of PPM images in the P6 format. It can also resize images according to a uniform scale. 

## Installation

```bash
$ git clone https://github.com/UA-CSC433-Fall2018/asgmt02-nsilvestri
$ cd asgmt02-nsilvestri
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Execution
```bash
$ ./prog01 path_to_ppm [(output_file scale)]
```
#### Example
```bash
$ ./prog01 ../data/construction.ppm small_construction.ppm .5
```

## Usage

While running the program:
* `q` increases gain by .05
* `a` decreases gain by .05
* `w` increases bias by .05
* `s` decreases bias by .05
* `e` increases gamma by .05
* `d` decreases gamma by .05
* `r` resizes the image by the scale provided at the command line and writes it to the file provided at the command line.
* `c` performs a 3x3 Guassian kernel convolution on the current image.
* `RETURN` writes the overwrites the currently edited file.

## Testing

There are some Catch2 tests in the `test/` directory. Compile them with the makefile provided. Unit tests are not complete, at all, and really only exist for my sake. Because I wrote a bug into the code.

## Notes

Code has been tested on cambridge. Tested to work on all images in the `data/` directory, as well as some other images that were found online.

I started doxygen/Javadoc style comments for some of it. They're incomplete now. Laziness.

#### Known Bugs

Data loss can occur when scaling any factor and undoing it.

Resizing an image to a smaller image convolutes the current image. It's not really a bug, just lazy programming because I've been working on this all day and just want it to be done now. I mean, I spent 3 hours trying to track down a segfault and it ended up just being because I didn't allocate space for a buffer used by memcpy. Catch me later. But, like, I think this is a damn good framework so far. I mean, I've cut a lot of corners but the outline for something really good is there.
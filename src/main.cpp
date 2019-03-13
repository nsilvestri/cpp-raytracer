// C++ includes
#include <iostream>
#include <cfloat>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

// custom includes
#include "PPMImage.hpp"
#include "Scene.hpp"

/**
 * Main function.  Initializes an SDL window, renderer, and texture,
 * and then goes into a loop to listen to events and draw the texture.
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return integer indicating success (0) or failure (nonzero)
 */
int main(int argc, char **argv)
{
	std::string inputFile;
	std::string outputFile;
	if (argc == 3)
	{	
		inputFile = argv[1];
		outputFile = argv[2];
	}
	else
	{
		std::cout << "Usage:" << std::endl;
		std::cout << "  ./prog01 scene_file output_ppm" << std::endl;
		exit(1);
	}

	Scene scene = Scene();
	scene.readSceneFile(inputFile);
	PPMImage image = scene.capture();
	image.write(outputFile);

	return 0;
}

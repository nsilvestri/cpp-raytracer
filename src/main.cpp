// include SDL2 libraries
#include <SDL.h>

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
 * Log an SDL error with some error message to the output stream of our
 * choice
 *
 * @param os The output stream to write the message to
 * @param msg The error message to write, SDL_GetError() appended to it
 */
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
 * the texture's width and height
 *
 * @param tex The source texture we want to draw
 * @param ren The renderer we want to draw to
 * @param x The x coordinate to draw to
 * @param y The y coordinate to draw to
 */
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

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

	// Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	// Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Basic SDL Test", 100, 100, image.getCols(), image.getRows(), SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// The textures we'll be using
	SDL_Texture *background;

	// Initialize the texture. SDL_PIXELFORMAT_RGB24 specifies 3 bytes per
	// pixel, one per color channel
	background = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, image.getCols(), image.getRows());
	// Copy the raw data array into the texture.
	SDL_UpdateTexture(background, NULL, image.getData(), 3 * image.getCols());
	if (background == NULL)
	{
		logSDLError(std::cout, "CreateTextureFromSurface");
	}

	// Make sure they both loaded ok
	if (background == NULL)
	{
		SDL_DestroyTexture(background);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Variables used in the rendering loop
	SDL_Event event;
	bool quit = false;
	bool leftMouseButtonDown = false;
	int start_mouseX;
	int start_mouseY;
	float orig_x_angle;
	float orig_y_angle;

	// initialize a 3x3 Guassian kernel
	int** kernel = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		kernel[i] = new int[3];
	}
	kernel[0][0] = 1;
	kernel[0][1] = 2;
	kernel[0][2] = 1;
	kernel[1][0] = 2;
	kernel[1][1] = 4;
	kernel[1][2] = 2;
	kernel[2][0] = 1;
	kernel[2][1] = 2;
	kernel[2][2] = 1;

	while (!quit)
	{
		// Grab the time for frame rate computation
		const Uint64 start = SDL_GetPerformanceCounter();

		// Clear the screen
		SDL_RenderClear(renderer);

		// Event Polling
		// This while loop responds to mouse and keyboard commands.
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_RETURN:
						image.write(outputFile);
						break;
					default:
						break;
        		}
			}
		}

		// Update the texture, assuming data has changed.
		SDL_UpdateTexture(background, NULL, image.getData(), 3 * image.getCols());
		// display the texture on the screen
		renderTexture(background, renderer, 0, 0);
		// Update the screen
		SDL_RenderPresent(renderer);

		// Display the frame rate to stdout
		const Uint64 end = SDL_GetPerformanceCounter();
		const static Uint64 freq = SDL_GetPerformanceFrequency();
		const double seconds = (end - start) / static_cast<double>(freq);
		// You may want to comment this line out for debugging purposes
		// std::cout << "Frame time: " << seconds * 1000.0 << "ms" << std::endl;
	}

	// After the loop finishes (when the window is closed, or escape is
	// pressed, clean up the data that we allocated.
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

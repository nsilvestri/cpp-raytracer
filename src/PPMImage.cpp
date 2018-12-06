#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

#include "PPMImage.hpp"
#include "RGBColor.hpp"

/* Constructors */

PPMImage::PPMImage(std::string filepath)
{
    this->filepath = filepath;

    std::ifstream infile(filepath.c_str());
    std::string line;

    /* Parse header of file */

    // make sure first line is P6
    getline(infile, line);
	if ("P6" != line)
	{
        std::cout << "File is not P6 format (Found: '" << line << "')." << std::endl;
		exit(1);
	}

	// skip comments
	do
	{
		getline(infile, line);
	}
	while (line.at(0) == '#');

	// get dimensions by splitting the current line
	char* dup = strdup(line.c_str()); // turned to char array to use strtok()
	std::string token = strtok(dup, " ");
	this->cols = atoi(token.c_str());
	token = strtok(NULL, " ");
	this->rows = atoi(token.c_str());
	free(dup);

	// get maxValue by parsing next line
	do
	{
		getline(infile, line);
	}
	while (line.at(0) == '#');
	this->maxValue = atoi(line.c_str());

	/* this->pixels is a 2D array of pointers to locations within
	 * the single block of memory created by pixels1d */
	this->pixels = new RGBColor*[this->rows];
	RGBColor* pixels1d = new RGBColor[this->rows * this->cols];
	this->pixels[0] = pixels1d;
	for (int y = 1; y < this->rows; y++)
	{
		this->pixels[y] = pixels[y - 1] + this->cols;
	}

    /* get image data from file */
	unsigned char ch;
	for (int i = 0; i < this->rows * this->cols; i++)
	{
		infile >> std::noskipws >> ch;
    	unsigned char r = ch;
		infile >> std::noskipws >> ch;
		unsigned char g = ch;
		infile >> std::noskipws >> ch;
		unsigned char b = ch;
		RGBColor* p = new RGBColor(r / 255.0, g / 255.0, b / 255.0);
		pixels1d[i] = *p;
	}
	this->regenerateData();
}

PPMImage::PPMImage(RGBColor* pixArray, int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->maxValue = 255;
	
	this->pixels = new RGBColor*[this->rows];
	RGBColor* pixels1d = new RGBColor[this->rows * this->cols];
	this->pixels[0] = pixels1d;
	for (int y = 1; y < this->rows; y++)
	{
		this->pixels[y] = pixels[y - 1] + this->cols;
	}
	
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			this->pixels[r][c] = pixArray[r * cols + c];
		}
	}
	this->regenerateData();
}

PPMImage::~PPMImage()
{
    delete this->data;
	delete this->pixels;
}

/* Other functions */

void PPMImage::rescale(float gain, float bias, float gamma)
{
	for (int r = 0; r < this->rows; r++)
	{
		for (int c = 0; c < this->cols; c++)
		{
			float pixelLuminance = this->getPixelAt(r, c).getLuminance();
			float newLuminance = std::pow(((gain * pixelLuminance) + bias), gamma);
			float scale = newLuminance / pixelLuminance;
			if (r == 0 && c == 0)
			{
				std::cout << this->getPixelAt(r, c).getLuminance() << std::endl;
			}
			this->getPixelAt(r, c).scale(scale);
			if (r == 0 && c == 0)
			{
				std::cout << this->getPixelAt(r, c).getLuminance() << std::endl;
			}
		}
	}
	this->regenerateData();
}

void PPMImage::write(std::string filepath)
{
	std::ofstream outputFile;
	outputFile.open(filepath.c_str());
	outputFile << "P6" << std::endl;
	outputFile << this->cols << " " << this->rows << std::endl;
	outputFile << this->maxValue << std::endl;
	outputFile.write((const char*) this->data, this->cols * this->rows * 3);
	outputFile.close();
}

void PPMImage::convolve(int** kernel, int kernelRows, int kernelCols)
{
	// require the kernel have a center pixel
	if (kernelRows % 2 == 0 || kernelCols % 2 == 0)
	{
		throw std::invalid_argument("Kernel has an even dimension");
	}

	// loop over each pixel in image
	for (int imgR = 0; imgR < this->rows; imgR++)
	{
		for (int imgC = 0; imgC < this->cols; imgC++)
		{
			// sum of values in kernel squares uncropped
			float kSum = 0;

			// sums of each channel
			float rSum = 0;
			float gSum = 0;
			float bSum = 0;

			// loop over each pixel in kernel
			for (int kernelR = 0; kernelR < kernelRows; kernelR++)
			{
				for (int kernelC = 0; kernelC < kernelCols; kernelC++)
				{
					int pixelRow = imgR + kernelR - (kernelRows / 2);
					int pixelCol = imgC + kernelC - (kernelCols / 2);

					// check that we didn't go out of bounds
					if (pixelRow < 0 || pixelCol < 0 ||
					    pixelRow >= this->rows || pixelCol > this->cols)
					{
						continue;
					}

					// get the pixel relative to the center of the kernel
					RGBColor& p = this->getPixelAt(pixelRow, pixelCol);

					int kVal = kernel[kernelR][kernelC];
					kSum += kVal;

					rSum += kVal * p.getR();
					gSum += kVal * p.getG();
					bSum += kVal * p.getB();
				}
			}

			float rAvg = (rSum / kSum);
			float gAvg = (gSum / kSum);
			float bAvg = (bSum / kSum);

			this->getPixelAt(imgR, imgC).setRGB(rAvg, gAvg, bAvg);
		}
	}
}

/* Setters/Getters */

unsigned char* PPMImage::getData() {
	return this->data;
}

std::string PPMImage::getFilepath() {
	return this->filepath;
}

int PPMImage::getRows() {
	return this->rows;
}

int PPMImage::getCols() {
	return this->cols;
}

int PPMImage::getMaxValue() {
	return this->maxValue;
}

RGBColor& PPMImage::getPixelAt(int row, int col)
{
	return this->pixels[row][col];
}

/* Private Functions */

void PPMImage::regenerateData()
{
	this->data = new unsigned char[this->cols * this->rows * 3];
    std::string newData = "";
	for (int r = 0; r < this->rows; r++)
	{
		for (int c = 0; c < this->cols; c++)
		{
			RGBColor& p = this->getPixelAt(r, c);
			newData += (unsigned char)(p.getR() * 255);
			newData += (unsigned char)(p.getG() * 255);
			newData += (unsigned char)(p.getB() * 255);
		}
	}
	memcpy(this->data, newData.c_str(), newData.length());
}
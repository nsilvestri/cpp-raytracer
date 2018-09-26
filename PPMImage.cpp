/**
 * @file PPMImage.cpp
 * @brief Object to represent a PPM Image in P6 format
 * @author Nick Silvestri <nsilvestri@email.arizona.edu>
 * @date 2018-09-02
 */

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

#include "PPMImage.hpp"
#include "RGBColor.hpp"

/**
 * Constructor for PPMImage.
 * 
 * @param filepath The location of the PPMImage this object represents.
 */
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

    /* get image data from file */
    //A raw data array of chars.
	this->data = new unsigned char[this->cols * this->rows * 3];
    std::string rawData = "";

	this->pixels = new RGBColor[this->rows * this->cols];

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
		pixels[i] = *p;
	}
	this->regenerateData();
}

PPMImage::PPMImage(RGBColor** pixArray, int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;
	this->maxValue = 255;
	
	this->pixels = new RGBColor[this->rows * this->cols];
	for (int i = 0; i < this->rows * this->cols; i++)
	{
		float r = pixArray[i]->getR();
		float g = pixArray[i]->getG();
		float b = pixArray[i]->getB();
		RGBColor* p = new RGBColor(r, g, b);
		pixels[i] = *p;
	}
	this->regenerateData();
}

/**
 * Destructor for PPMImage.
 */ 
PPMImage::~PPMImage()
{
    delete this->data;
	delete this->pixels;
}

/**
 * Rescale the image based on the given parameters.
 * 
 * @param gain the gain to adjust the image by
 * @param bias the bias to adjust the image by
 * @param gamma the gamma to adjust the image by
 */ 
void PPMImage::rescale(float gain, float bias, float gamma)
{
	for (int i = 0; i < this->rows * this->cols; i++)
	{
		float pixelLuminance = pixels[i].getLuminance();
		float newLuminance = std::pow(((gain * pixelLuminance) + bias), gamma);
		float scale = newLuminance / pixelLuminance;
		pixels[i].scale(scale);
	}
	this->regenerateData();
}

/**
 * Private helper method that is called after the image is rescaled.
 * Recalculates the data buffer according to the array of RGBColors.
 */
void PPMImage::regenerateData()
{
	this->data = new unsigned char[this->cols * this->rows * 3];
    std::string newData = "";
	for (int i = 0; i < this->rows * this->cols; i++)
	{
		newData += (unsigned char)(pixels[i].getR() * 255);
		newData += (unsigned char)(pixels[i].getG() * 255);
		newData += (unsigned char)(pixels[i].getB() * 255);
	}
	memcpy(this->data, newData.c_str(), newData.length());
}

/**
 * Returns a pointer to the array of raw data for this image.
 * 
 * @return a pointer to the array raw data for this image.
 */
unsigned char* PPMImage::getData() {
	return this->data;
}

/**
 * Return the filepath that this image was read from, as a string.
 * 
 * @return a string representing the filepath that this image was retrived from.
 */
std::string PPMImage::getFilepath() {
	return this->filepath;
}

/**
 * Return the number of rows in this image as an int.
 * 
 * @return the number of rows in this image as an int.
 */
int PPMImage::getRows() {
	return this->rows;
}

/**
 * Return the number of columns in this image as an int.
 * 
 * @return the number of columns in this image as an int.
 */
int PPMImage::getCols() {
	return this->cols;
}

/**
 * Returns the maximum value for a pixel in this image, as an int.
 * 
 * @return the maximum value for a pixel in this image, as an int.
 */
int PPMImage::getMaxValue() {
	return this->maxValue;
}

RGBColor* PPMImage::getPixelAt(int row, int col)
{
	return &(this->pixels[row * this->getCols() + col]);
}

/**
 * Writes this image to the file specified by the filepath.
 * @param filepath the file to write this image to
 */
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

void PPMImage::resize(float scale, std::string filepath)
{
	// just write the current image to file if the scale is 1
	if (scale == 1.0)
	{
		this->write(filepath);
		return;
	}

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

	// if the output image is smaller, convolve the source
	if (scale < 1.0)
	{
		this->convolve(kernel, 3, 3);
	}

	//create an output image scaled k times
	int newWidth = this->cols * scale;
	int newHeight = this->rows * scale;
	RGBColor** newPixels =
				new RGBColor*[newHeight * newWidth];

	// use nearest neighbor to resize
	for (int row = 0; row < newHeight; row++)
	{
		for (int col = 0; col < newWidth; col++)
		{
			int x = (int)(col * this->cols / (float) newWidth);
			int y = (int)(row * this->rows / (float) newHeight);

			RGBColor* p = this->getPixelAt(y, x);

			RGBColor* newP = new RGBColor(p->getR(), p->getG(), p->getB());

			newPixels[row * newWidth + col] = newP;
		}
	}
	PPMImage* newImage = new PPMImage(newPixels, newHeight, newWidth);

	// if the output image is larger, convolve the output
	if (scale > 1.0)
	{
		newImage->convolve(kernel, 3, 3);
	}

	newImage->write(filepath);
	std::cout << "Wrote file to " << filepath << std::endl;
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
					RGBColor* p = this->getPixelAt(pixelRow, pixelCol);

					int kVal = kernel[kernelR][kernelC];
					kSum += kVal;

					rSum += kVal * p->getR();
					gSum += kVal * p->getG();
					bSum += kVal * p->getB();
				}
			}

			float rAvg = (rSum / kSum);
			float gAvg = (gSum / kSum);
			float bAvg = (bSum / kSum);

			this->getPixelAt(imgR, imgC)->setRGB(rAvg, gAvg, bAvg);
		}
	}
}
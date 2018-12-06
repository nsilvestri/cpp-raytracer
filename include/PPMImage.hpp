#pragma once

#include <string>

#include "RGBColor.hpp"

class PPMImage
{
    private:
        RGBColor** pixels;
        unsigned char* data;
        std::string filepath;
        int rows;
        int cols;
        int maxValue;

        /**
         * Private helper method that is called after the image is rescaled.
         * Recalculates the data buffer according to the array of RGBColors.
         */
        void regenerateData();
    public:

        /* Constructors */

        /**
         * Constructor for PPMImage. Loads an existing PPM image from a file.
         * 
         * @param filepath The location of the PPMImage this object represents.
         */
        PPMImage(std::string filepath);
        PPMImage(RGBColor* pixels, int rows, int cols);
        ~PPMImage();

        /* Other functions */

        /**
         * Rescale the image based on the given parameters.
         * 
         * @param gain the gain to adjust the image by
         * @param bias the bias to adjust the image by
         * @param gamma the gamma to adjust the image by
         */ 
        void rescale(float gain, float bias, float gamma);

        /**
         * Writes this image to the PPM file specified by the filepath.
         * 
         * @param filepath the file to write this image to
         */
        void write(std::string filepath);

        /**
         * Performs a convolution on this image with the given kernel with the
         * specified number of rows and columns.
         * 
         * @param kernel a pointer to the 2D int array representing the kernel
         *        to convolve this image by.
         * @param rows the number of rows in the kernel.
         * @param cols the number of cols in the kernel.
         */
        void convolve(int** kernel, int rows, int cols);

        /* Getters/Setters */

        /**
         * Returns a pointer to the array of raw data for this image.
         * 
         * @return a pointer to the array raw data for this image.
         */
        unsigned char* getData();

        /**
         * Return the filepath that this image was read from, as a string.
         * 
         * @return a string representing the filepath that this image was retrived from.
         */
        std::string getFilepath();

        /**
         * Return the number of rows in this image as an int.
         * 
         * @return the number of rows in this image as an int.
         */
        int getRows();

        /**
         * Return the number of columns in this image as an int.
         * 
         * @return the number of columns in this image as an int.
         */
        int getCols();

        /**
         * Returns the maximum value for a pixel in this image, as an int.
         * 
         * @return the maximum value for a pixel in this image, as an int.
         */
        int getMaxValue();

        /**
         * Returns a pointer to the RGBColor object at the given indices in the image.
         *
         * @param row the row of the requested pixel
         * @parram col the column of the requested pixel
         */
        RGBColor& getPixelAt(int row, int col);
};


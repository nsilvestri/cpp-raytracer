#pragma once

#include <string>

#include "RGBPixel.hpp"

class PPMImage
{
    private:
        RGBPixel* pixels;
        unsigned char* data;
        std::string filepath;
        int rows;
        int cols;
        int maxValue;
        void regenerateData();
    public:
        PPMImage(std::string filepath);
        PPMImage(RGBPixel** pixels, int width, int height);
        ~PPMImage();
        void rescale(float gain, float bias, float gamma);
        unsigned char* getData();
        std::string getFilepath();
        int getRows();
        int getCols();
        int getMaxValue();
        RGBPixel* getPixelAt(int row, int col);
        void write(std::string filepath);
        void resize(float scale, std::string filepath);
        void convolve(int** kernel, int rows, int cols);
};


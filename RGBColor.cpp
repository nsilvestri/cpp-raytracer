/**
 * @file RGBColor.cpp
 * @brief Class representing a single RGB24 pixel.
 * @author Nick Silvestri <nsilvestri@email.arizona.edu>
 * @date 2018-09-20
 */

#include <stdexcept>
#include <string>
#include "RGBColor.hpp"

/**
 * Constructor for RGBColor using floats. Value must be between 0 and
 * 1, inclusive, or this will throw std::invalid_argument.
 * 
 * @throw std::invalid_argument
 * 
 * @param r the value of the r channel for this pixel, from 0 to 1
 * @param g the value of the g channel for this pixel, from 0 to 1
 * @param b the value of the b channel for this pixel, from 0 to 1
 */
RGBColor::RGBColor(float r, float g, float b)
{
    this->setRGB(r, g, b);
}

/**
 * Default onstructor for RGBColor. Sets all values to 0.
 */
RGBColor::RGBColor()
{
    this->setRGB(0, 0, 0);
}

/**
 * Destructor for RGBColor.
 * Doesn't actually do anything.
 */
RGBColor::~RGBColor()
{
    // wowie
}

/**
 * Returns a float representing the brightness of the pixel, in the range of 0
 * to 1.
 * The luminance equation used is (20R + 40G + B) / 61
 */ 
float RGBColor::getLuminance()
{
    return ((20 * r) + (40 * g) + (b)) / 61.0;
}

/**
 * Scales all three channels of the pixel by the given value. The resulting
 * value will be clamped to be between 0 and 255, inclusive.
 */
void RGBColor::scale(float scale)
{
    this->setR(RGBColor::clamp(this->getR() * scale));
    this->setG(RGBColor::clamp(this->getG() * scale));
    this->setB(RGBColor::clamp(this->getB() * scale));
}

/**
 * Returns the float value given, clamped between 0 and 255, inclusive.
 * @return the clamped value, clamped between 0 and 255, inclusive.
 */
float RGBColor::clamp(float f)
{
    if (f < 0)
    {
        return 0;
    }
    else if (f > 1)
    {
        return 1;
    }
    else
    {
        return f;
    }
}

/**
 * Return the R value of this pixel.
 * @return the R value of this pixel.
 */
float RGBColor::getR()
{
    return this->r;
}

/**
 * Return the G value of this pixel.
 * @return the G value of this pixel.
 */
float RGBColor::getG()
{
    return this->g;
}

/**
 * Return the B value of this pixel.
 * @return the B value of this pixel.
 */
float RGBColor::getB()
{
    return this->b;
}

/**
 * Set the R value of this pixel.
 * @param r the new value of the R channel
 */
void RGBColor::setR(float r)
{
    if (r < 0 || r > 1)
    {
        throw std::invalid_argument(
            "Received value for r outside range of 0 to 1: r = " 
            + std::to_string(r));
    }
    this->r = r;
}

/**
 * Set the G value of this pixel.
 * @param g the new value of the G channel
 */
void RGBColor::setG(float g)
{
    if (g < 0 || g > 1)
    {
        throw std::invalid_argument(
            "Received value for g outside range of 0 to 1: g = " 
            + std::to_string(g));
    }
    this->g = g;
}

/**
 * Set the B value of this pixel.
 * @param B the new value of the B channel
 */
void RGBColor::setB(float b)
{
    if (b < 0 || b > 1)
    {
        throw std::invalid_argument(
            "Received value for b outside range of 0 to 1: b = " 
            + std::to_string(b));
    }
    this->b = b;
}

/**
 * Set all values for all 3 channels of this pixel. Value must be between 0 and
 * 1, inclusive, or this will throw std::invalid_argument.
 * 
 * @throw std::invalid_argument
 * @param R the new value of the R channel
 * @param G the new value of the G channel
 * @param B the new value of the B channel
 */
void RGBColor::setRGB(float r, float g, float b)
{
    this->setR(r);
    this->setG(g);
    this->setB(b);
}
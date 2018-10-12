#include "Surface.hpp"
#include "RGBColor.hpp"

void Surface::setAmbient(RGBColor ambient)
{
    this->ambient = ambient;
}

void Surface::setDiffuse(RGBColor diffuse)
{
    this->diffuse = diffuse;
}

void Surface::setSpecular(RGBColor specular)
{
    this->specular = specular;
}

void Surface::setPhong(float phong)
{
    this->phong = phong;
}
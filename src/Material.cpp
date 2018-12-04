#include "Material.hpp"

Material::Material()
{
    
}

Material::Material(RGBColor ambient, RGBColor diffuse, RGBColor specular, float phongExponent)
{
    this->setAmbient(ambient);
    this->setDiffuse(diffuse);
    this->setSpecular(specular);
    this->setPhongExponent(phongExponent);
}

void Material::setAmbient(RGBColor ambient)
{
    this->ambient = ambient;
}

void Material::setDiffuse(RGBColor diffuse)
{
    this->diffuse = diffuse;
}

void Material::setSpecular(RGBColor specular)
{
    this->specular = specular;
}

void Material::setPhongExponent(float phongExponent)
{
    this->phongExponent = phongExponent;
}

RGBColor Material::getAmbient() const
{
    return this->ambient;
}

RGBColor Material::getDiffuse() const
{
    return this->diffuse;
}

RGBColor Material::getSpecular() const
{
    return this->specular;
}

float Material::getPhongExponent() const
{
    return this->phongExponent;
}
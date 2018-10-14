#include "Material.hpp"

Material::Material(RGBColor ambient, RGBColor diffuse, RGBColor specular)
{
    this->setAmbient(ambient);
    this->setDiffuse(diffuse);
    this->setSpecular(specular);
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
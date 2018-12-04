#include "Surface.hpp"
#include "Material.hpp"

Surface::Surface() {}

void Surface::setMaterial(Material material)
{
    this->material = material;
}

Material Surface::getMaterial() const
{
    return this->material;
}
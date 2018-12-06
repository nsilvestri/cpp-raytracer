#include "Light.hpp"
#include "Vector3D.hpp"
#include "RGBColor.hpp"

Light::Light()
{
    this->setPosition(Vector3D(0, 0, 0));
    this->setColor(RGBColor(1, 1, 1));
}

Light::Light(Vector3D position, RGBColor color)
{
    this->setPosition(position);
    this->setColor(color);
}

Light::Light(const Light& l)
{
    this->setPosition(l.getPosition());
    this->setColor(l.getColor());
}

Vector3D Light::getPosition() const
{
    return this->position;
}

RGBColor Light::getColor() const
{
    return this->color;
}

void Light::setPosition(Vector3D position)
{
    this->position = position;
}

void Light::setColor(RGBColor color)
{
    this->color = color;
}
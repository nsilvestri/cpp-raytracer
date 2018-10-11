#include "Sphere.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "IntersectionRecord.hpp"

Sphere::Sphere()
{

}

Sphere::Sphere(Vector3D position, float radius)
{
    this->setPosition(position);
    this->setRadius(radius);
}

Vector3D Sphere::getPosition() const
{
    return this->position;
}

float Sphere::getRadius() const
{
    return this->radius;
}

void Sphere::setPosition(Vector3D position)
{
    this->position = position;
}

void Sphere::setRadius(float radius)
{
    this->radius = radius;
}

bool Sphere::intersect(IntersectionRecord& result, Ray3D r)
{
    return false;
}
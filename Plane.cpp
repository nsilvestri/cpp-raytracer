#include "Plane.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "IntersectionRecord.hpp"

Plane::Plane()
{

}

Plane::Plane(Vector3D position, Vector3D normal)
{
    this->setPosition(position);
    this->setNormal(normal);
}

Vector3D Plane::getPosition() const
{
    return this->position;
}

Vector3D Plane::getNormal() const
{
    return this->normal;
}

void Plane::setPosition(Vector3D position)
{
    this->position = position;
}

void Plane::setNormal(Vector3D normal)
{
    this->normal = normal;
}

bool Plane::intersect(IntersectionRecord& result, Ray3D r)
{
    return false;
}
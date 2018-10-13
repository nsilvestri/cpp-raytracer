#include <iostream>

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

bool Sphere::intersect(IntersectionRecord& result, Ray3D ray)
{
    // a, b, c are the A, B, C in the quadtratic equation
    float a = ray.getDirection().dot(ray.getDirection());
    float b = (ray.getDirection() * 2).dot(
            ray.getOrigin() - this->getPosition());
    float c = (ray.getOrigin() - this->getPosition()).dot(
            (ray.getOrigin() - this->getPosition())) -
            (this->getRadius() * this->getRadius());

    // D = B^2-4AC
    float discriminant = (b * b) - (4 * a * c);
    // std::cout << ray << ": " << discriminant << std::endl;
    if (discriminant < 0)
    {
        return false;
    }
    return true;
}
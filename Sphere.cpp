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
    float quadraticA = ray.getDirection().dot(ray.getDirection());
    float quadraticB = (ray.getDirection() * 2).dot(
            ray.getOrigin() - this->getPosition());
    float quadraticC = (ray.getOrigin() - this->getPosition()).dot(
            (ray.getOrigin() - this->getPosition())) - (this->getRadius() * this->getRadius());

    // D = B^2-4AC
    float discriminant = (quadraticB * quadraticB) - (4 * quadraticA * quadraticC);

    if (discriminant < 0)
    {
        return false;
    }
    return true;
}
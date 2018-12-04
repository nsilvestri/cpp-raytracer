#include <iostream>
#include <math.h>

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

    // a = (d . d)
    float a = ray.getDirection().dot(ray.getDirection());
    // b = (d . (e - c))
    float b = (ray.getDirection() * 2).dot(
               ray.getOrigin() - this->getPosition());
    // c = (rayPos - center) . (rayPos - center) - R^2
    float c = ((ray.getOrigin() - this->getPosition()).dot(
              (ray.getOrigin() - this->getPosition()))) -
              (this->getRadius() * this->getRadius());

    // D = B^2-4AC
    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
    {
        return false;
    }

    float tPlus = (-b + sqrt(discriminant)) / (2 * a);
    float tMinus = (-b - sqrt(discriminant)) / (2 * a);

    float t = fmin(tPlus, tMinus);

    // point on ray is P(t) = e + td
    result.pointOfIntersection = ray.getOrigin() + (ray.getDirection() * t);
    result.normalAtIntersection = (result.pointOfIntersection - this->getPosition()) * (1 / this->getRadius());
    result.t = t;
    result.surfaceIntersected = this;

    return true;
}
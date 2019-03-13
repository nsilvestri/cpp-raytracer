#include <iostream>
#include <math.h>

#include "Ray3D.hpp"
#include "Vector3D.hpp"


Ray3D::Ray3D(Vector3D origin, Vector3D direction)
{
    this->setOrigin(origin);
    this->setDirection(direction.normalize());
}

Ray3D::Ray3D()
{
    this->setOrigin(Vector3D(0, 0, 0));
    this->setDirection(Vector3D(0, 0, 0));
}

Ray3D::Ray3D(const Ray3D& r)
{
    this->setOrigin(r.getOrigin());
    this->setDirection(r.getDirection().normalize());
}

Vector3D Ray3D::getOrigin() const
{
    return this->origin;
}

Vector3D Ray3D::getDirection() const
{
    return this->direction;
}

void Ray3D::setOrigin(Vector3D origin)
{
    this->origin = origin;
}

void Ray3D::setDirection(Vector3D direction)
{
    this->direction = direction.normalize();
}

bool Ray3D::isPointOn(Vector3D point) const
{
    Vector3D pointDirection = point - this->getOrigin();
    float xScale = point.getX() / this->getDirection().getX();
    std::cout << xScale << std::endl;
    float yScale = point.getY() / this->getDirection().getY();
    std::cout << yScale << std::endl;
    float zScale = point.getZ() / this->getDirection().getZ();
    std::cout << zScale << std::endl;

    /* a point must be on the origin or in the direction of ray.direction
     * relative to the origin, and all scales must be equal
     */
    return (xScale >= 0 && xScale == yScale && yScale == zScale);
}

std::ostream& operator<<(std::ostream &stream, const Ray3D& r)
{
    return stream << "Ray3D(Origin=" << r.getOrigin() <<
            ", direction=" << r.getDirection() << ")";
}

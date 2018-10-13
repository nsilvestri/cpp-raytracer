#include <math.h>

#include "Ray3D.hpp"
#include "Vector3D.hpp"

/**
 * Constructor for Ray3D. Creates a new Ray3D object based on the given origin
 * and direction, given as Vector3D objects.
 * @param origin the origin of this new Ray3D
 * @param direction the direction of this new Ray3D
 */
Ray3D::Ray3D(Vector3D origin, Vector3D direction)
{
    this->setOrigin(origin);
    this->setDirection(direction);
}

/**
 * Default constructor of Ray3D. Sets the origin and direction to Vector3Ds with
 * initial values of 0.
 */
Ray3D::Ray3D()
{
    this->setOrigin(Vector3D(0, 0, 0));
    this->setDirection(Vector3D(0, 0, 0));
}

/**
 * Copy constructor for Ray3D
 */
Ray3D::Ray3D(const Ray3D& r)
{
    this->setOrigin(r.getOrigin());
    this->setDirection(r.getDirection());
}

/**
 * Gets the origin of this Ray3D as a Vector3D.
 * @returns the origin of this Ray3D as a Vector3D.
 */
Vector3D Ray3D::getOrigin() const
{
    return this->origin;
}

/**
 * Gets the direction of this Ray3D as a Vector3D.
 * @returns the direction of this Ray3D as a Vector3D.
 */
Vector3D Ray3D::getDirection() const
{
    return this->direction;
}

/**
 * Sets the origin of this Ray3D to the given origin.
 * @param origin the new origin to set this Ray3D to.
 */
void Ray3D::setOrigin(Vector3D origin)
{
    this->origin = origin;
}

/**
 * Sets the direction of this Ray3D to the given direction.
 * @param direction the new direction to set this Ray3D to.
 */
void Ray3D::setDirection(Vector3D direction)
{
    this->direction = direction;
}

/**
 * Determines if the given Vector3D, interpreted as a point, lies on this Ray3D.
 * @param point the Vector3D point to check if it lies on this Ray3D.
 */
bool Ray3D::isPointOn(Vector3D point) const
{
    // TODO
}

std::ostream& operator<<(std::ostream &stream, const Ray3D& r)
{
    return stream << "Ray3D(Origin=" << r.getOrigin() <<
            ", direction=" << r.getDirection() << ")";
}

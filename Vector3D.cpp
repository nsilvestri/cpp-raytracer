#include "Vector3D.hpp"

Vector3D::Vector3D(float x, float y, float z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

Vector3D::Vector3D()
{
    this->setX(0);
    this->setY(0);
    this->setZ(0);
}

Vector3D::Vector3D(const Vector3D& v)
{
    this->setX(v.getX());
    this->setY(v.getY());
    this->setZ(v.getZ());
}

float Vector3D::getX() const
{
    return this->x;
}

float Vector3D::getY() const
{
    return this->y;
}

float Vector3D::getZ() const
{
    return this->z;
}

void Vector3D::setX(float x)
{
    this->x = x;
}

void Vector3D::setY(float y)
{
    this->y = y;
}

void Vector3D::setZ(float z)
{
    this->z = z;
}

//return *this is a typical assignment operator syntax, so that you can
//chain multiple assignments, e.g. a = b = c
Vector3D Vector3D::operator=(const Vector3D& rhs) {
  this->x = rhs.getX();
  this->y = rhs.getY();
  this->z = rhs.getZ();

  return *this;
}

Vector3D Vector3D::operator+(const Vector3D& rhs)
{
    Vector3D newVec(*this);
    newVec.setX(newVec.getX() + rhs.getX());
    newVec.setY(newVec.getY() + rhs.getY());
    newVec.setZ(newVec.getZ() + rhs.getZ());

    return newVec;
}

/**
 * Scale the vector by the given scalar.
 * 
 * @param scalar the value to scale the vector by
 * @return a new vector equal to the original vector scaled by the scalar
 */
Vector3D Vector3D::operator*(float scalar)
{
    Vector3D newVec(*this);
    newVec.setX(newVec.getX() * scalar);
    newVec.setY(newVec.getY() * scalar);
    newVec.setZ(newVec.getZ() * scalar);

    return newVec;
}

float Vector3D::dot(Vector3D other)
{
    return this->getX() * other.getX() 
                + this->getY() * other.getY() 
                + this->getZ() * other.getZ();
}

Vector3D Vector3D::cross(Vector3D other)
{
    Vector3D newVec(*this);

    return Vector3D(newVec.getY() * other.getZ() - newVec.getZ() * other.getY(),
                    newVec.getZ() * other.getX() - newVec.getX() * other.getZ(),
                    newVec.getX() * other.getY() - newVec.getY() * other.getX());
}
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

//return *this is a typical assignment operator syntax, so that you can
//chain multiple assignments, e.g. a = b = c
Vector3D Vector3D::operator=(const Vector3D& rhs) {
  this->x = rhs.getX();
  this->y = rhs.getY();
  this->z = rhs.getZ();

  return *this;
}

Vector3D Vector3D::operator*(float scalar)
{
    Vector3D newVec(*this);
    newVec.setX(this->getX() * scalar);
    newVec.setY(this->getY() * scalar);
    newVec.setZ(this->getZ() * scalar);

    return newVec;
}
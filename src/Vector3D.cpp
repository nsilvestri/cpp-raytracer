#include <math.h>
#include <iostream>

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

/**
 * Return the length of this Vector3D.
 * 
 * @return the length of this Vector3D.
 */
float Vector3D::length() const
{
    return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
}

/**
 * Normalizes this vector; i.e. changes the length of this vector to 1 while
 * preserving direction. If the length of this vector is 0, nothing happens to
 * this vector.
 * @return this vector after normalization
 */
Vector3D Vector3D::normalize()
{
    float length = this->length();
    if (length == 0) return *this;
    // this = this / length(this)
    *this = *this * (1.0 / length);
    return *this;
}

/**
 * Typical assignment operator.
 */
Vector3D Vector3D::operator=(const Vector3D& rhs) {
  this->x = rhs.getX();
  this->y = rhs.getY();
  this->z = rhs.getZ();

  return *this;
}

/**
 * Add this vector with another vector.
 * 
 * @param rhs the Vector3D on the right hand side of the + operator.
 * @return the result of the add operator.
 */
Vector3D Vector3D::operator+(const Vector3D& rhs)
{
    Vector3D newVec(*this);
    newVec.setX(newVec.getX() + rhs.getX());
    newVec.setY(newVec.getY() + rhs.getY());
    newVec.setZ(newVec.getZ() + rhs.getZ());

    return newVec;
}

/**
 * Subtracts this vector with another vector.
 * 
 * @param rhs the Vector3D on the right hand side of the - operator.
 * @return the result of the subtraction operation.
 */
Vector3D Vector3D::operator-(const Vector3D& rhs)
{
    Vector3D newVec(*this);
    newVec.setX(newVec.getX() - rhs.getX());
    newVec.setY(newVec.getY() - rhs.getY());
    newVec.setZ(newVec.getZ() - rhs.getZ());

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

bool Vector3D::operator==(const Vector3D& rhs) const
{
    return !(this->compare(rhs));
}

bool Vector3D::operator!=(const Vector3D& rhs) const
{
    return !(*this == rhs);
}

int Vector3D::compare(const Vector3D& other) const
{
    if (this->getX() != other.getX() ||
        this->getY() != other.getY() ||
        this->getZ() != other.getZ())
    {
        return -1;
    }

    return 0;
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& v)
{
    return stream << "Vector3D(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
}

/**
 * Compute the dot product between this vector and another vector.
 *
 * @param other the other vector to compute the dot product with.
 * @return the result of the dot product
 */
float Vector3D::dot(Vector3D other)
{
    return this->getX() * other.getX() 
                + this->getY() * other.getY() 
                + this->getZ() * other.getZ();
}

/**
 * Computer the cross product between this vector and another vector.
 * 
 * @param other the other vector to compute the cross product with.
 * @return the Vector3D representing the result of the cross product.
 */
Vector3D Vector3D::cross(Vector3D other)
{
    Vector3D newVec(*this);

    return Vector3D(newVec.getY() * other.getZ() - newVec.getZ() * other.getY(),
                    newVec.getZ() * other.getX() - newVec.getX() * other.getZ(),
                    newVec.getX() * other.getY() - newVec.getY() * other.getX());
}
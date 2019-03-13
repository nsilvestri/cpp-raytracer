#pragma once

#include <iostream>

class Vector3D
{
    private:
        float x;
        float y;
        float z;
    public:
        Vector3D();
        Vector3D(float x, float y, float z);
        Vector3D(const Vector3D& v);

        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float x);
        void setY(float y);
        void setZ(float z);

        /**
         * Return the length of this Vector3D.
         * 
         * @return the length of this Vector3D.
         */
        float length() const;

        /**
         * Normalizes this vector; i.e. changes the length of this vector to 1 while
         * preserving direction. If the length of this vector is 0, nothing happens to
         * this vector.
         * 
         * @return this vector after normalization
         */
        Vector3D normalize();

        /**
         * Typical assignment operator.
         */
        Vector3D operator=(const Vector3D& rhs);

        /**
         * Adds this vector with another vector, element-wise.
         * 
         * @param rhs the Vector3D on the right hand side of the + operator.
         * @return the result of the addition.
         */
        Vector3D operator+(const Vector3D& rhs);

        /**
         * Subtracts this vector with another vector, element wise.
         * 
         * @param rhs the Vector3D on the right hand side of the - operator.
         * @return the result of the subtraction.
         */
        Vector3D operator-(const Vector3D& rhs);
        
        /**
         * Scale this vector by the given scalar.
         * 
         * @param scalar the value to scale the vector by
         * @return a new vector equal to the original vector scaled by the scalar
         */
        Vector3D operator*(float scalar);
        bool operator==(const Vector3D& rhs) const;
        bool operator!=(const Vector3D& rhs) const;
        int compare(const Vector3D& other) const;
        friend std::ostream& operator<<(std::ostream &stream, const Vector3D& v);

        /**
         * Compute the dot product between this vector and another vector.
         *
         * @param other the other vector to compute the dot product with.
         * @return the result of the dot product
         */
        float dot(Vector3D other);
        
        /**
         * Computer the cross product between this vector and another vector.
         * 
         * @param other the other vector to compute the cross product with, on
         * the right side of the cross product.
         * @return the Vector3D representing the result of the cross product.
         */
        Vector3D cross(Vector3D other);
};


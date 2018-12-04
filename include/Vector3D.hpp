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

        float length() const;
        Vector3D normalize();

        Vector3D operator=(const Vector3D& rhs);
        Vector3D operator+(const Vector3D& rhs);
        Vector3D operator-(const Vector3D& rhs);
        Vector3D operator*(float scalar);
        bool operator==(const Vector3D& rhs) const;
        bool operator!=(const Vector3D& rhs) const;
        int compare(const Vector3D& other) const;
        friend std::ostream& operator<<(std::ostream &stream, const Vector3D& v);

        float dot(Vector3D other);
        Vector3D cross(Vector3D other);
};


#pragma once

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
        void normalize();

        Vector3D operator=(const Vector3D& rhs);
        Vector3D operator+(const Vector3D& rhs);
        Vector3D operator-(const Vector3D& rhs);
        Vector3D operator*(float scalar);
        float dot(Vector3D other);
        Vector3D cross(Vector3D other);
};


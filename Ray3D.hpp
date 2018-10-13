#pragma once

#include "Vector3D.hpp"

class Ray3D
{
    private:
        Vector3D origin;
        Vector3D direction;
    public:
        Ray3D();
        Ray3D(Vector3D origin, Vector3D direction);
        Ray3D(const Ray3D& r);

        Vector3D getOrigin() const;
        Vector3D getDirection() const;

        void setOrigin(Vector3D origin);
        void setDirection(Vector3D direction);

        bool isPointOn(Vector3D point) const;

        friend std::ostream& operator<<(std::ostream &stream, const Ray3D& r);

};


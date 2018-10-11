#pragma once

#include "Vector3D.hpp"

class Plane : public Surface
{
    private:
        Vector3D position;
        Vector3D normal;
    public:
        Plane();
        Plane(Vector3D position,Vector3D normal);

        Vector3D getPosition();
        Vector3D getNormal();

        void setPosition(Vector3D position);
        void setNormal(Vector3D normal);

        bool intersect(IntersectionRecord& result, Ray3D r);
};
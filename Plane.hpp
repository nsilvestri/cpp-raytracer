#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "IntersectionRecord.hpp"

class Plane : public Surface
{
    private:
        Vector3D position;
        Vector3D normal;
    public:
        Plane();
        Plane(Vector3D position,Vector3D normal);

        Vector3D getPosition() const;
        Vector3D getNormal() const;

        void setPosition(Vector3D position);
        void setNormal(Vector3D normal);

        bool intersect(IntersectionRecord& result, Ray3D r);
};
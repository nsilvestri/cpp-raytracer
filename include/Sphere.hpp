#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"

class Sphere : public Surface
{
    private:
        Vector3D position;
        float radius;
    public:
        Sphere();
        Sphere(Vector3D position, float radius);

        Vector3D getPosition() const;
        float getRadius() const;

        void setPosition(Vector3D position);
        void setRadius(float radius);

        bool intersect(IntersectionRecord& result, Ray3D r);
};


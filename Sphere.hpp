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
        bool intersect(IntersectionRecord &result, Ray3D r);
};


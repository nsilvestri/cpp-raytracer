#pragma once

#include "Ray3D.hpp"

class Surface
{
    private:

    public:
        virtual bool intersect(IntersectionRecord &result, Ray3D r);
};


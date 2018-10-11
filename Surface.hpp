#pragma once

#include "Ray3D.hpp"
#include "IntersectionRecord.hpp"

class Surface
{
    private:

    public:
        virtual bool intersect(IntersectionRecord &result, Ray3D r);
};


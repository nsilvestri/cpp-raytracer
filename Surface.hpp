#pragma once

#include "Ray3D.hpp"
#include "Material.hpp"
#include "IntersectionRecord.hpp"

class Surface
{
    private:
        Material material;
    public:
        Surface();
          
        virtual bool intersect(IntersectionRecord& result, Ray3D r) = 0;

        void setMaterial(Material material);
        Material getMaterial() const;
};


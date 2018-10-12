#pragma once

#include "Ray3D.hpp"
#include "RGBColor.hpp"
#include "IntersectionRecord.hpp"

class Surface
{
    private:
        RGBColor ambient;
        RGBColor diffuse;
        RGBColor specular;
        float phong;
    public:        
        virtual bool intersect(IntersectionRecord &result, Ray3D r) = 0;

        void setAmbient(RGBColor ambient);
        void setDiffuse(RGBColor diffuse);
        void setSpecular(RGBColor specular);
        void setPhong(float phong);
};


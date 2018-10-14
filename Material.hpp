#pragma once

#include "RGBColor.hpp"

class Material
{
    private:
        RGBColor ambient;
        RGBColor diffuse;
        RGBColor specular;
        float phong;
    public:
        Material(RGBColor ambient, RGBColor diffuse, RGBColor specular);

        void setAmbient(RGBColor ambient);
        void setDiffuse(RGBColor diffuse);
        void setSpecular(RGBColor specular);
        RGBColor getAmbient() const;
        RGBColor getDiffuse() const;
        RGBColor getSpecular() const;
}
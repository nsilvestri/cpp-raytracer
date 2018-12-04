#pragma once

#include "RGBColor.hpp"

class Material
{
    private:
        RGBColor ambient;
        RGBColor diffuse;
        RGBColor specular;
        float phongExponent;
    public:
        Material();
        Material(RGBColor ambient, RGBColor diffuse, RGBColor specular, float phongExponent);

        void setAmbient(RGBColor ambient);
        void setDiffuse(RGBColor diffuse);
        void setSpecular(RGBColor specular);
        void setPhongExponent(float phongExponent);
        RGBColor getAmbient() const;
        RGBColor getDiffuse() const;
        RGBColor getSpecular() const;
        float getPhongExponent() const;
};
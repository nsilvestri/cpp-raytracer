#pragma once

#include "Vector3D.hpp"
#include "RGBColor.hpp"

class Light
{
    private:
        Vector3D position;
        RGBColor color;
    
    public:
        Light();
        Light(Vector3D position, RGBColor color);
        Light(const Light& l);

        Vector3D getPosition() const;
        RGBColor getColor() const;

        void setPosition(Vector3D position);
        void setColor(RGBColor color);
};

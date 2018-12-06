#pragma once

#include "Vector3D.hpp"
#include "RGBColor.hpp"

class Light
{
    private:
        Vector3D position;
        RGBColor color;
    
    public:
        /**
         * Default constructor for Light. Initializes the position to the XYZ origin and
         * sets the color to maximum white (255, 255, 255).
         */
        Light();
        Light(Vector3D position, RGBColor color);
        Light(const Light& l);

        Vector3D getPosition() const;
        RGBColor getColor() const;

        void setPosition(Vector3D position);
        void setColor(RGBColor color);
};

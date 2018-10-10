#pragma once

#include "Vector3D.hpp"
#include "RGBColor.hpp"

class Light
{
    private:
        Vector3D position;
        RGBColor color;
    
    public:
        Light(Vector3D position, RGBColor color);
        
}
#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "RGBColor.hpp"

class Camera
{
    private:
        Vector3D eye;
        Vector3D lookat;
        Vector3D up;
        float fov;
        
    public:
        RGBColor** capture();
};


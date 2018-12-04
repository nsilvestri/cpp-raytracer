#pragma once

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp" 
#include "Light.hpp"
#include "PPMImage.hpp"
#include "RGBColor.hpp"
#include "Ray3D.hpp"

class Scene
{
    private:
        Camera camera;
        std::vector<Surface*> surfaces;
        std::vector<Light> lights;

        RGBColor castRay(Ray3D ray);

    public:
        Scene();

        void readSceneFile(std::string filepath);

        PPMImage capture();


};
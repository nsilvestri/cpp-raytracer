#pragma once

#include <vector>

#include "Camera.hpp"
#include "Surface.hpp" 
#include "Light.hpp"
#include "PPMImage.hpp"

class Scene
{
    private:
        Camera camera;
        std::vector<Surface*> surfaces;
        std::vector<Light> lights;

    public:
        Scene();

        void readSceneFile(std::string filepath);

        PPMImage capture();
};
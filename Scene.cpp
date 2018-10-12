#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "Scene.hpp"
#include "Camera.hpp"
#include "Surface.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

Scene::Scene()
{
    this->camera = Camera();
    this->surfaces = std::vector<Surface*>();
    this->lights = std::vector<Light>();
}

void Scene::readSceneFile(std::string filepath)
{
    std::ifstream infile(filepath.c_str());

    /* Parse header of file */

    // make sure first line is P6
    std::string line;
    while (std::getline(infile, line))
    {
        std::string buf;
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        while (ss >> buf)
        {
            tokens.push_back(buf);
        }

        /* if / else to determine what the line is setting */

        // set eye vector (camera pos)
        if (tokens.at(0).compare("e") == 0)
        {
            Vector3D cameraPosition = Vector3D(atof(tokens.at(1).c_str()),
                                               atof(tokens.at(2).c_str()),
                                               atof(tokens.at(3).c_str()));

            this->camera.setPosition(cameraPosition);
        }
        // set lookat vector (image pos)
        else if (tokens.at(0).compare("l") == 0)
        {
            Vector3D imagePosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            this->camera.setImagePosition(imagePosition);
        }
        // define up vector of camera
        else if (tokens.at(0).compare("u") == 0)
        {
            Vector3D up = Vector3D(atof(tokens.at(1).c_str()),
                                   atof(tokens.at(2).c_str()),
                                   atof(tokens.at(3).c_str()));
            this->camera.defineUp(up);
        }
        // set camera FOV
        else if (tokens.at(0).compare("f") == 0)
        {
            this->camera.setFov(atof(tokens.at(1).c_str()));
        }
        // set image dimensions
        else if (tokens.at(0).compare("i") == 0)
        {
            this->camera.setHorizontalResolution(atoi(tokens.at(1).c_str()));
            this->camera.setVerticalResolution(atoi(tokens.at(2).c_str()));
        }
        // add light to scene
        else if (tokens.at(0).compare("L") == 0)
        {
            Vector3D lightPosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            RGBColor lightColor = RGBColor(atof(tokens.at(4).c_str()),
                                           atof(tokens.at(5).c_str()),
                                           atof(tokens.at(6).c_str()));
            this->lights.push_back(Light(lightPosition, lightColor));
        }
        // add Sphere to scene
        else if (tokens.at(0).compare("S") == 0)
        {
            Vector3D spherePosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            float radius = atof(tokens.at(4).c_str());
            this->surfaces.push_back(new Sphere(spherePosition, radius));
        }
        // add light to scene
        else if (tokens.at(0).compare("P") == 0)
        {
            Vector3D pointPosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            Vector3D planeNormal = Vector3D(atof(tokens.at(4).c_str()),
                                            atof(tokens.at(5).c_str()),
                                            atof(tokens.at(6).c_str()));
            this->surfaces.push_back(new Plane(pointPosition, planeNormal));
        }
        // error handling for unknown line identifier
        else
        {
            std::cerr << "Unknown line format in scene file. Skipping line." << std::endl;
        }
    }
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

#include "easylogging++.h"

#include "Scene.hpp"
#include "Camera.hpp"
#include "Surface.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "RGBColor.hpp"
#include "PPMImage.hpp"

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

            LOG(DEBUG) << "Set camera position to " << cameraPosition;
        }
        // set lookat vector (image pos)
        else if (tokens.at(0).compare("l") == 0)
        {
            Vector3D imagePosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            this->camera.setImagePosition(imagePosition);
            
            LOG(DEBUG) << "Set image position to " << imagePosition;
        }
        // define up vector of camera
        else if (tokens.at(0).compare("u") == 0)
        {
            Vector3D up = Vector3D(atof(tokens.at(1).c_str()),
                                   atof(tokens.at(2).c_str()),
                                   atof(tokens.at(3).c_str()));
            this->camera.defineUp(up);
            LOG(DEBUG) << "Defined camera's up to " << up;
        }
        // set camera FOV
        else if (tokens.at(0).compare("f") == 0)
        {
            this->camera.setFov(atof(tokens.at(1).c_str()));
            
            LOG(DEBUG) << "Set camera FOV to " << this->camera.getFov();
        }
        // set image dimensions
        else if (tokens.at(0).compare("i") == 0)
        {
            this->camera.setHorizontalResolution(atoi(tokens.at(1).c_str()));
            this->camera.setVerticalResolution(atoi(tokens.at(2).c_str()));

            LOG(DEBUG) << "Set image resolution to " << 
                    this->camera.getHorizontalResolution() <<
                    "x" <<
                    this->camera.getVerticalResolution();
        }
        // add light to scene
        else if (tokens.at(0).compare("L") == 0)
        {
            Vector3D lightPosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));

            // read and tokenize next line for color
            std::getline(infile, line);
            std::stringstream ss1(line);
            std::vector<std::string> tokens1;
            while (ss1 >> buf)
            {
                tokens1.push_back(buf);
            }

            RGBColor lightColor = RGBColor(atof(tokens1.at(0).c_str()),
                                           atof(tokens1.at(1).c_str()),
                                           atof(tokens1.at(2).c_str()));
            this->lights.push_back(Light(lightPosition, lightColor));
            LOG(DEBUG) << "Added Light at " << lightPosition <<
                    " of color " << lightColor;
        }
        // add Sphere to scene
        else if (tokens.at(0).compare("S") == 0)
        {
            Vector3D spherePosition = Vector3D(atof(tokens.at(1).c_str()),
                                               atof(tokens.at(2).c_str()),
                                               atof(tokens.at(3).c_str()));
            float radius = atof(tokens.at(4).c_str());

            Sphere* newSphere = new Sphere(spherePosition, radius);

            /* Get diffuse, ambient, specular from the next 3 lines */

            // read and tokenize next line for ambient
            std::getline(infile, line);
            std::stringstream ss1(line);
            std::vector<std::string> tokens1;
            while (ss1 >> buf)
            {
                tokens1.push_back(buf);
            }

            RGBColor ambient = RGBColor(atof(tokens1.at(0).c_str()),
                                        atof(tokens1.at(1).c_str()),
                                        atof(tokens1.at(2).c_str()));

            // read and tokenize next line for diffuse
            std::getline(infile, line);
            std::stringstream ss2(line);
            std::vector<std::string> tokens2;
            while (ss2 >> buf)
            {
                tokens2.push_back(buf);
            }

            RGBColor diffuse = RGBColor(atof(tokens2.at(0).c_str()),
                                        atof(tokens2.at(1).c_str()),
                                        atof(tokens2.at(2).c_str()));

            // read and tokenize next line for specular
            std::getline(infile, line);
            std::stringstream ss3(line);
            std::vector<std::string> tokens3;
            while (ss3 >> buf)
            {
                tokens3.push_back(buf);
            }

            RGBColor specular = RGBColor(atof(tokens3.at(0).c_str()),
                                         atof(tokens3.at(1).c_str()),
                                         atof(tokens3.at(2).c_str()));

            // set ambient, diffuse, and specular for new sphere
            newSphere->setAmbient(ambient);
            newSphere->setDiffuse(diffuse);
            newSphere->setSpecular(specular);

            /* read in one more value for Phong exponent */
            std::getline(infile, line);
            newSphere->setPhong(atof(line.c_str()));

            this->surfaces.push_back(newSphere);
            LOG(DEBUG) << "Added sphere at " << spherePosition <<
                    " of radius " << radius;
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

            Plane* newPlane = new Plane(pointPosition, planeNormal);

            // read and tokenize next line for ambient
            std::getline(infile, line);
            std::stringstream ss1(line);
            std::vector<std::string> tokens1;
            while (ss1 >> buf)
            {
                tokens1.push_back(buf);
            }

            RGBColor ambient = RGBColor(atof(tokens1.at(0).c_str()),
                                        atof(tokens1.at(1).c_str()),
                                        atof(tokens1.at(2).c_str()));

            // read and tokenize next line for diffuse
            std::getline(infile, line);
            std::stringstream ss2(line);
            std::vector<std::string> tokens2;
            while (ss2 >> buf)
            {
                tokens2.push_back(buf);
            }

            RGBColor diffuse = RGBColor(atof(tokens2.at(0).c_str()),
                                        atof(tokens2.at(1).c_str()),
                                        atof(tokens2.at(2).c_str()));

            // read and tokenize next line for specular
            std::getline(infile, line);
            std::stringstream ss3(line);
            std::vector<std::string> tokens3;
            while (ss3 >> buf)
            {
                tokens3.push_back(buf);
            }

            RGBColor specular = RGBColor(atof(tokens3.at(0).c_str()),
                                         atof(tokens3.at(1).c_str()),
                                         atof(tokens3.at(2).c_str()));

            // set ambient, diffuse, and specular for new sphere
            newPlane->setAmbient(ambient);
            newPlane->setDiffuse(diffuse);
            newPlane->setSpecular(specular);

            /* read in one more value for Phong exponent */
            std::getline(infile, line);
            newPlane->setPhong(atof(line.c_str()));
            
            this->surfaces.push_back(newPlane);
            LOG(DEBUG) << "Added plane at " << pointPosition <<
                    " with normal " << planeNormal;
        }
        // error handling for unknown line identifier
        else
        {
            std::cerr << "Unknown line format in scene file. Skipping line." << std::endl;
        }
    }
}

PPMImage Scene::capture()
{
    int imageRows = this->camera.getVerticalResolution();
    int imageCols = this->camera.getHorizontalResolution();
    RGBColor** pixels2d = new RGBColor*[imageRows];
	RGBColor* pixels1d = new RGBColor[imageRows * imageCols];
	pixels2d[0] = pixels1d;
	for (int y = 1; y < imageRows; y++)
	{
		pixels2d[y] = pixels2d[y - 1] + this->camera.getHorizontalResolution();
	}

    Ray3D** rays = this->camera.generateRays();
    for (int r = 0; r < imageRows; r++)
    {
        for (int c = 0; c < imageCols; c++)
        {
            Ray3D ray = rays[r][c];
            for (int s = 0; s < surfaces.size(); s++)
            {
                IntersectionRecord ir;
                bool intersected = surfaces.at(s)->intersect(ir, ray);

                if (intersected)
                {
                    pixels2d[r][c] = RGBColor(1, 1, 1);
                }
                else
                {
                    pixels2d[r][c] = RGBColor(0, 0, 0);
                }
            }
        }
    }
    PPMImage image = PPMImage(*pixels2d, imageCols, imageRows);
    return image;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <math.h>

#include "easylogging++.h"

#include "Scene.hpp"
#include "Camera.hpp"
#include "Surface.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "RGBColor.hpp"
#include "PPMImage.hpp"
#include "Material.hpp"

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

            LOG(INFO) << "Set camera position to " << cameraPosition;
        }
        // set lookat vector (image pos)
        else if (tokens.at(0).compare("l") == 0)
        {
            Vector3D imagePosition = Vector3D(atof(tokens.at(1).c_str()),
                                              atof(tokens.at(2).c_str()),
                                              atof(tokens.at(3).c_str()));
            this->camera.setImagePosition(imagePosition);
            
            LOG(INFO) << "Set image position to " << imagePosition;
        }
        // define up vector of camera
        else if (tokens.at(0).compare("u") == 0)
        {
            Vector3D up = Vector3D(atof(tokens.at(1).c_str()),
                                   atof(tokens.at(2).c_str()),
                                   atof(tokens.at(3).c_str()));
            this->camera.defineUp(up);
            LOG(INFO) << "Defined camera's up to " << up;
        }
        // set camera FOV
        else if (tokens.at(0).compare("f") == 0)
        {
            this->camera.setFov(atof(tokens.at(1).c_str()));
            
            LOG(INFO) << "Set camera FOV to " << this->camera.getFov();
        }
        // set image dimensions
        else if (tokens.at(0).compare("i") == 0)
        {
            this->camera.setHorizontalResolution(atoi(tokens.at(1).c_str()));
            this->camera.setVerticalResolution(atoi(tokens.at(2).c_str()));

            LOG(INFO) << "Set image resolution to " << 
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
            LOG(INFO) << "Added Light at " << lightPosition <<
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

            /* read in one more value for Phong exponent */
            std::getline(infile, line);
            float phongExponent = atof(line.c_str());

            // set ambient, diffuse, and specular for new sphere
            Material material = Material(ambient, diffuse, specular, phongExponent);
            newSphere->setMaterial(material);


            this->surfaces.push_back(newSphere);
            LOG(INFO) << "Added sphere at " << spherePosition <<
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

            /* read in one more value for Phong exponent */
            std::getline(infile, line);
            float phongExponent = atof(line.c_str());

            // set ambient, diffuse, and specular for new sphere
            Material material = Material(ambient, diffuse, specular, phongExponent);
            newPlane->setMaterial(material);
            
            this->surfaces.push_back(newPlane);
            LOG(INFO) << "Added plane at " << pointPosition <<
                    " with normal " << planeNormal;
        }
        // error handling for unknown line identifier
        else
        {
            std::cerr << "Unknown line format in scene file. Skipping line." << std::endl;
        }
    }
}

/**
 * Generates and returns a PPMImage object representing the view from the Camera
 * object in this scene.
 * @return a PPMImage representing the view from the camera in this scene.
 */
PPMImage Scene::capture()
{
    // just get dimensions now, saves horizontal space later
    int imageRows = this->camera.getVerticalResolution();
    int imageCols = this->camera.getHorizontalResolution();

    // create the array of RGBColor data. 1d array with 2d-array indexes
    RGBColor** pixels2d = new RGBColor*[imageRows];
	RGBColor* pixels1d = new RGBColor[imageRows * imageCols];
	pixels2d[0] = pixels1d;
	for (int y = 1; y < imageRows; y++)
	{
		pixels2d[y] = pixels2d[y - 1] + imageCols;
	}

    // create the rays, and for each ray check that it
    Ray3D** rays = this->camera.generateRays();
    for (int r = 0; r < imageRows; r++)
    {
        for (int c = 0; c < imageCols; c++)
        {
            Ray3D ray = rays[r][c];
            for (int s = 0; s < surfaces.size(); s++)
            {
                Surface* currentSurface = surfaces.at(s);
                IntersectionRecord ir;
                bool intersected = currentSurface->intersect(ir, ray);

                if (!intersected)
                {
                    pixels2d[r][c] = RGBColor(0, 0, 0);
                    continue;
                }

                /* Shading calculations */
                
                float lambR = 0;
                float lambG = 0;
                float lambB = 0;

                float specR = 0;
                float specG = 0;
                float specB = 0;

                for (int l = 0; l < lights.size(); l++)
                {
                    Light currentLight = lights.at(l);
                    Ray3D rayToLight = Ray3D(ir.pointOfIntersection, currentLight.getPosition() - ir.pointOfIntersection);

                    // check if point is in shadow
                    for (int i = 0; i < surfaces.size(); i++)
                    {
                        IntersectionRecord temp;
                        if (!surfaces.at(i)->intersect(temp, rayToLight))
                        {
                            // Calculate Lambertian and specular shading
                            float lambMax = fmax(0, ir.normalAtIntersection.dot(rayToLight.getDirection()));
                            float kR = currentSurface->getMaterial().getDiffuse().getR();
                            float kG = currentSurface->getMaterial().getDiffuse().getG();
                            float kB = currentSurface->getMaterial().getDiffuse().getB();

                            float intensity = currentLight.getColor().getLuminance() / 2;
                            // float intensity = .1;
                            lambR += kR * intensity * lambMax;
                            lambG += kG * intensity * lambMax;
                            lambB += kB * intensity * lambMax;

                            // calculate blinn-phong shading
                            Vector3D half = ((this->camera.getPosition() - ir.pointOfIntersection) + currentLight.getPosition()).normalize();
                            float specMax = pow(fmax(0, ir.normalAtIntersection.normalize().dot(half)), currentSurface->getMaterial().getPhongExponent());
                            float sR = currentSurface->getMaterial().getSpecular().getR();
                            float sG = currentSurface->getMaterial().getSpecular().getG();
                            float sB = currentSurface->getMaterial().getSpecular().getB();

                            specR += sR * specMax;
                            specG += sG * specMax;
                            specB += sB * specMax;
                        }
                    }
                }               

                // calculate ambient
                float ambientIntensity = .1;
                float ambR = currentSurface->getMaterial().getAmbient().getR() * ambientIntensity;
                float ambG = currentSurface->getMaterial().getAmbient().getG() * ambientIntensity;
                float ambB = currentSurface->getMaterial().getAmbient().getB() * ambientIntensity;


                pixels2d[r][c] = RGBColor(lambR + specR + ambR, lambG + specG + ambG, lambB + specB + ambB);
                break;
            }
        }
    }
    PPMImage image = PPMImage(*pixels2d, imageRows, imageCols);
    return image;
}
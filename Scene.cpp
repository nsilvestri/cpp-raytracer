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

    // create the rays, and calculate the color for each ray
    Ray3D** rays = this->camera.generateRays();
    for (int r = 0; r < imageRows; r++)
    {
        for (int c = 0; c < imageCols; c++)
        {
            RGBColor color = this->castRay(rays[r][c]);

            pixels2d[r][c] = color;
        }
    }
    PPMImage image = PPMImage(*pixels2d, imageRows, imageCols);
    return image;
}

RGBColor Scene::castRay(Ray3D ray)
{
    // check the ray against all surfaces
    IntersectionRecord* closestIntersection = NULL;
    for (int s = 0; s < surfaces.size(); s++)
    {
        Surface* currentSurface = surfaces.at(s);
        IntersectionRecord* ir = (IntersectionRecord*)malloc(sizeof *ir);
        bool intersected = currentSurface->intersect(*ir, ray);

        // if there's no intersect, then we can skip shading
        if (!intersected)
        {
            continue;
        }

        // if we did intersect, check that it's the closest so far.
        if (closestIntersection == NULL || ir->t < closestIntersection->t)
        {
            closestIntersection = ir;
        }
        else
        {
            continue;
        }
    }

    if (closestIntersection == NULL)
    {
        return RGBColor(0, 0, 0);
    }

    /* Shading calculations */
    
    float lambR = 0;
    float lambG = 0;
    float lambB = 0;

    float specR = 0;
    float specG = 0;
    float specB = 0;

    float shadR = 0;
    float shadG = 0;
    float shadB = 0;

    // calculate shading based on every light source
    Surface* currentSurface = closestIntersection->surfaceIntersected;
    for (int l = 0; l < lights.size(); l++)
    {
        Light currentLight = lights.at(l);
        float intensity = currentLight.getColor().getLuminance() / 3;
        // offset origin to avoid self-intersection. Sometimes works.
        Ray3D rayToLight = Ray3D(closestIntersection->pointOfIntersection + (closestIntersection->normalAtIntersection * 0.00001), currentLight.getPosition() - closestIntersection->pointOfIntersection);

        // check if point is in shadow by seeing if the light ray intersects with a surface
        for (int i = 0; i < surfaces.size(); i++)
        {
            IntersectionRecord temp;
            if (!surfaces.at(i)->intersect(temp, rayToLight))
            {
                // Calculate Lambertian and specular shading
                float lambMax = fmax(0, closestIntersection->normalAtIntersection.dot(rayToLight.getDirection()));
                float dR = currentSurface->getMaterial().getDiffuse().getR() + currentLight.getColor().getR() * intensity;
                float dG = currentSurface->getMaterial().getDiffuse().getG() + currentLight.getColor().getG() * intensity;
                float dB = currentSurface->getMaterial().getDiffuse().getB() + currentLight.getColor().getB() * intensity;

                lambR += dR * intensity * lambMax;
                lambG += dG * intensity * lambMax;
                lambB += dB * intensity * lambMax;

                // calculate blinn-phong shading
                Vector3D half = ((this->camera.getPosition() - closestIntersection->pointOfIntersection) + currentLight.getPosition()).normalize();
                float specMax = pow(fmax(0, closestIntersection->normalAtIntersection.normalize().dot(half)), currentSurface->getMaterial().getPhongExponent());
                float sR = currentSurface->getMaterial().getSpecular().getR() + currentLight.getColor().getR() * intensity / 3;
                float sG = currentSurface->getMaterial().getSpecular().getG() + currentLight.getColor().getG() * intensity / 3;
                float sB = currentSurface->getMaterial().getSpecular().getB() + currentLight.getColor().getB() * intensity / 3;

                specR += sR * specMax;
                specG += sG * specMax;
                specB += sB * specMax;
            }
            // calculate shadow light
            shadR += currentLight.getColor().getR() * intensity / 10;
            shadG += currentLight.getColor().getG() * intensity / 10;
            shadB += currentLight.getColor().getB() * intensity / 10;
        }
    }               

    // calculate ambient
    float ambientIntensity = .1;
    float ambR = currentSurface->getMaterial().getAmbient().getR() * ambientIntensity;
    float ambG = currentSurface->getMaterial().getAmbient().getG() * ambientIntensity;
    float ambB = currentSurface->getMaterial().getAmbient().getB() * ambientIntensity;
    
    return RGBColor(lambR + specR + ambR + shadR, lambG + specG + ambG + shadG, lambB + specB + ambB + shadB);
}
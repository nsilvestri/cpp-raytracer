#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <math.h>

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

    // calculate shading based on every light source

    // stores the colors generated by checking each light, to be averaged later


    Surface* currentSurface = closestIntersection->surfaceIntersected;
    RGBColor c = currentSurface->getMaterial().getAmbient();
    for (int l = 0; l < lights.size(); l++)
    {
        Light currentLight = lights.at(l);

        /* check if point is in shadow by seeing if the light ray intersects with a surface */

        bool shadowed = false;
        // offset origin to avoid self-intersection.
        float lightDistance = (currentLight.getPosition() - closestIntersection->pointOfIntersection).length();
        Vector3D lightDirection = (currentLight.getPosition() - closestIntersection->pointOfIntersection).normalize();
        Ray3D rayToLight = Ray3D(closestIntersection->pointOfIntersection, lightDirection);
        for (int i = 0; i < surfaces.size(); i++)
        {
            IntersectionRecord temp;
            if (surfaces.at(i)->intersect(temp, rayToLight))
            {
                // 8e-3 is the offset to prevent self-intersection; avoids random dark spots
                if (temp.t > 8e-3 && temp.t < lightDistance)
                {
                    shadowed = true;
                    break;
                }
            }
        }

        /* Add color if not shadowed */

        if (!shadowed)
        {
            /* calculate Lambertian */
            RGBColor diffuse = currentSurface->getMaterial().getDiffuse();

            float lambMax = fmax(0, closestIntersection->normalAtIntersection.normalize().dot(rayToLight.getDirection().normalize()));
            float dR = diffuse.getR() * currentLight.getColor().getR();
            float dG = diffuse.getG() * currentLight.getColor().getG();
            float dB = diffuse.getB() * currentLight.getColor().getB();

            float lambR = dR * lambMax;
            float lambG = dG * lambMax;
            float lambB = dB * lambMax;

            /* calculate specular */
            RGBColor specular = currentSurface->getMaterial().getSpecular();

            Vector3D half = ((this->camera.getPosition() - closestIntersection->pointOfIntersection).normalize() + rayToLight.getDirection()).normalize();
            float specMax = pow(fmax(0, closestIntersection->normalAtIntersection.normalize().dot(half)), currentSurface->getMaterial().getPhongExponent());
            float sR = specular.getR() * currentLight.getColor().getR();
            float sG = specular.getG() * currentLight.getColor().getG();
            float sB = specular.getB() * currentLight.getColor().getB();

            float specR = sR * specMax;
            float specG = sG * specMax;
            float specB = sB * specMax;

            c = RGBColor(c.getR() + lambR + specR, c.getG() + lambG + specG, c.getB() + lambB + specB);
        }
    }
    return c;
}
#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "RGBColor.hpp"

class Camera
{
    private:
        Vector3D position;
        Vector3D imagePosition; // also known as "lookat" vector
        Vector3D up;
        float fov;
        
        float imageDistance;

        Vector3D u;
        Vector3D v;
        Vector3D w;
        void calculateUVW();
        
    public:
        Camera(Vector3D position, Vector3D imageLocation, Vector3D up);
        Camera(const Vector3D& c);

        void setPosition(Vector3D position);
        void setImagePosition(Vector3D imagePosition);
        void defineUp(Vector3D up);

        Vector3D getPosition() const;
        Vector3D getImagePosition() const;
        Vector3D getUp() const;

        Ray3D** generateRays() const;
};


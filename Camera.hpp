#pragma once

#include "Surface.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"
#include "RGBColor.hpp"

class Camera
{
    private:
        /* Vectors accessible from setters/getters */
        Vector3D position;
        Vector3D imagePosition; // also known as "lookat" vector
        Vector3D up;
        float fov;
        int horizontalResolution;
        int verticalResolution;
        
        Vector3D u;
        Vector3D v;
        Vector3D w;
        void calculateUVW();

        float imageDistance;
        float top;
        float bottom;
        float left;
        float right;
        
    public:
        Camera(Vector3D position, Vector3D imageLocation, Vector3D up,
                int horizontalResolution, int verticalResolution, float fov);
        Camera();
        Camera(const Camera& c);

        void setPosition(Vector3D position);
        void setImagePosition(Vector3D imagePosition);
        void defineUp(Vector3D up);
        void setFov(float fov);
        void setHorizontalResolution(int horizontalResolution);
        void setVerticalResolution(int verticalResolution);

        Vector3D getPosition() const;
        Vector3D getImagePosition() const;
        Vector3D getUp() const;
        float getFov() const;
        int getHorizontalResolution() const;
        int getVerticalResolution() const;

        Ray3D** generateRays() const;
};


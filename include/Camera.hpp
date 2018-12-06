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

        /**
         * Private method to calculate u, v, and w of the orthnormal image basis. Each
         * vector is defined as follows:
         *      w = -1 * (cameraPosition - imagePosition)
         *      u = w x up
         *      v = u x w
         */
        void calculateUVW();

        float imageDistance;
        float top;
        float bottom;
        float left;
        float right;

        /**
         * Calculates the location of the edges of the image in UVW space.
         * 
         * Must be called every time
         */
        void calculateImagePoints();
        
    public:
        /* Constructors */
        Camera(Vector3D position, Vector3D imageLocation, Vector3D up,
                int horizontalResolution, int verticalResolution, float fov);
        Camera();
        Camera(const Camera& c);

        void setPosition(Vector3D position);
        void setImagePosition(Vector3D imagePosition);

        /**
         * Defines what is "up" for this camera. This may or may not be perpendicular to
         * w (i.e., parallel to the image plane). This method will recalculate u, v, and
         * w of the image basis when called.
         */
        void defineUp(Vector3D up);

        /**
         * Sets the field of view of this camera object.
         * @param fov the new field of view for this camera
         */
        void setFov(float fov);
        void setHorizontalResolution(int horizontalResolution);
        void setVerticalResolution(int verticalResolution);

        Vector3D getPosition() const;
        Vector3D getImagePosition() const;
        Vector3D getUp() const;
        float getFov() const;
        int getHorizontalResolution() const;
        int getVerticalResolution() const;

        /**
         * Calculates the rays to be cast from the camera through the image.
         * 
         * @return A 2D array of Ray3D objects, where the location of each Ray3D in the
         * array corresponds to the pixel in the image. The array returned has the same
         * dimensions as the image, as specified in getHorizontalResolution() and
         * getVerticalResolution().
         */
        Ray3D** generateRays();

        /**
         * Calculates the orthographic rays to be cast from the image, exactly
         * normal from each pixel in the image.
         * 
         * @return A 2D array of Ray3D objects, where the location of each Ray3D in the
         * array corresponds to the pixel in the image. The array returned has the same
         * dimensions as the image, as specified in getHorizontalResolution() and
         * getVerticalResolution().
         */
        Ray3D** generateOrthographicRays();
};


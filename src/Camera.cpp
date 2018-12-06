#include <math.h>
#include <iostream>

#include "Camera.hpp"
#include "Vector3D.hpp"
#include "Ray3D.hpp"

Camera::Camera(Vector3D position, Vector3D imagePosition, Vector3D up,
        int horizontalResolution, int verticalResolution, float fov)
{
    this->setPosition(position);
    this->setImagePosition(imagePosition);
    this->defineUp(up);

    this->setHorizontalResolution(horizontalResolution);
    this->setVerticalResolution(verticalResolution);
    this->setFov(fov);
}

Camera::Camera()
{

}

Camera::Camera(const Camera& c)
{
    this->setImagePosition(c.getImagePosition());
    this->defineUp(c.getUp());
}

void Camera::setPosition(Vector3D position)
{
    this->position = position;
}

void Camera::setImagePosition(Vector3D imagePosition)
{
    this->imagePosition = imagePosition;
}

void Camera::defineUp(Vector3D up)
{
    this->up = up;
    calculateUVW();
}

void Camera::calculateUVW()
{
    // create orthogonal basis
    this->w = (this->getImagePosition() - this->getPosition()) * -1;
    this->u = this->w.cross(this->up);
    this->v = this->u.cross(this->w);

    // normalize to create orthonormal basis
    this->w.normalize();
    this->u.normalize();
    this->v.normalize();
}

void Camera::setFov(float fov)
{
    this->fov = fov;
}

void Camera::setHorizontalResolution(int horizontalResolution)
{
    this->horizontalResolution = horizontalResolution;
}

void Camera::setVerticalResolution(int verticalResolution)
{
    this->verticalResolution = verticalResolution;
}

Vector3D Camera::getPosition() const
{
    return this->position;
}

Vector3D Camera::getImagePosition() const
{
    return this->imagePosition;
}

Vector3D Camera::getUp() const
{
    return this->up;
}

float Camera::getFov() const
{
    return this->fov;
}

int Camera::getHorizontalResolution() const
{
    return this->horizontalResolution;
}

int Camera::getVerticalResolution() const
{
    return this->verticalResolution;
}

Ray3D** Camera::generateRays()
{
    // calculate corners of image
    this->calculateImagePoints();

    // Create 2D array of arrays from 1D block of rays memory
	Ray3D* rays1d = new Ray3D[this->getHorizontalResolution() *
                                   this->getVerticalResolution()];
    Ray3D** rays2d = new Ray3D*[this->getVerticalResolution()];
    rays2d[0] = rays1d;
	for (int y = 1; y < this->getVerticalResolution(); y++)
	{
		rays2d[y] = rays2d[y - 1] + this->getHorizontalResolution();
	}

    // calculate ray for every pixel in image

    // d = (imagePos - camPos).length
    float dScalar = (this->getImagePosition() - this->getPosition()).length();
    for (int r = 0; r < this->getVerticalResolution(); r++)
    {
        for (int c = 0; c < this->getHorizontalResolution(); c++)
        {
            // u = l + (r - l)(c + 0.5)/horizRes
            float uScalar = this->left + (((this->right - this->left) * (c + 0.5)) / 
                    this->getHorizontalResolution());
            // v = b + (t - b)(r + 0.5)/vertRes
            float vScalar = this->bottom + (((this->top - this->bottom) * (r + 0.5)) / 
                    this->getVerticalResolution());

            // ray.direction = -dW + uU + vV
            Vector3D direction = (this->w * (-1 * dScalar)) +
                                 (this->u * uScalar) +
                                 (this->v * vScalar);
            // ray.origin = cameraPosition
            Vector3D origin = this->getPosition();
            Ray3D ray = Ray3D(origin, direction);
            rays2d[r][c] = ray;
        }
    }
    return rays2d;
}

Ray3D** Camera::generateOrthographicRays()
{
    // calculate corners of image
    this->calculateImagePoints();

    // Create 2D array of arrays from 1D block of rays memory
	Ray3D* rays1d = new Ray3D[this->getHorizontalResolution() *
                                   this->getVerticalResolution()];
    Ray3D** rays2d = new Ray3D*[this->getVerticalResolution()];
    rays2d[0] = rays1d;
	for (int y = 1; y < this->getVerticalResolution(); y++)
	{
		rays2d[y] = rays2d[y - 1] + this->getHorizontalResolution();
	}

    // calculate ray for every pixel in image
    for (int r = 0; r < this->getVerticalResolution(); r++)
    {
        for (int c = 0; c < this->getHorizontalResolution(); c++)
        {
            // u = l + (r - l)(c + 0.5)/horizRes
            float uScalar = (this->left + (this->right - this->left) * (c + 0.5)) / 
                    this->getHorizontalResolution();
            // v = b + (t - b)(r + 0.5)/vertRes
            float vScalar = (this->bottom + (this->top - this->bottom) * (r + 0.5)) / 
                    this->getVerticalResolution();

            // ray.direction = -dW + uU + vV
            Vector3D direction = this->w * -1;
            // ray.origin = cameraPosition
            Vector3D origin = (this->getPosition() +
                              (this->u * uScalar) +
                              (this->v * vScalar));
            Ray3D ray = Ray3D(origin, direction);
            rays2d[r][c] = ray;
        }
    }
    return rays2d;
}

void Camera::calculateImagePoints()
{
    this->top = -(imagePosition - position).length() * tan((fov / 2) * 3.14159265 / 180);
    this->bottom = -top;
    this->right = top * ((float) horizontalResolution / verticalResolution);
    this->left = -right;
}
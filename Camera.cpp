#include "Camera.hpp"

Camera::Camera(Vector3D position, Vector3D imagePosition, Vector3D up)
{
    this->setPosition(position);
    this->setImagePosition(imagePosition);
    this->defineUp(up);
}

Camera::Camera(const Camera& c)
{
    this->setPosition(c.getPosition());
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

/**
 * Defines what is "up" for this camera. This may or may not be perpendicular to
 * w (i.e., parallel to the image plane). This method will recalculate u, v, and
 * w of the image basis when called.
 */
void Camera::defineUp(Vector3D up)
{
    this->up = up;
    calculateUVW();
}

/**
 * Private method to recalculate u, v, and w of the image space basis. Each
 * vector is defined as follows:
 *      w = -1 * (cameraPosition - imagePosition)
 *      u = w x up
 *      v = u x w
 */
void Camera::calculateUVW()
{
    this->w = (this->getImagePosition() - this->getImagePosition()) * -1;
    this->u = this->w.cross(this->up);
    this->v = this->u.cross(this->w);

    this->w.normalize();
    this->u.normalize();
    this->v.normalize();
}
#pragma once

#include "Vector3D.hpp"

class Ray3D
{
    private:

        Vector3D origin;
        Vector3D direction;

    public:

        /**
         * Constructor for Ray3D. Creates a new Ray3D object based on the given origin
         * and direction, given as Vector3D objects.
         * @param origin the origin of this new Ray3D
         * @param direction the direction of this new Ray3D. The direction will be
         * normalized.
         */
        Ray3D(Vector3D origin, Vector3D direction);

        /**
         * Default constructor of Ray3D. Sets the origin and direction to Vector3Ds with
         * initial values of 0.
         */
        Ray3D();

        /**
         * Copy constructor for Ray3D
         */
        Ray3D(const Ray3D& r);

        /**
         * Gets the origin of this Ray3D as a Vector3D.
         * @returns the origin of this Ray3D as a Vector3D.
         */
        Vector3D getOrigin() const;

        /**
         * Gets the direction of this Ray3D as a Vector3D.
         * @returns the direction of this Ray3D as a Vector3D.
         */
        Vector3D getDirection() const;

        /**
         * Sets the origin of this Ray3D to the given origin.
         * @param origin the new origin to set this Ray3D to.
         */
        void setOrigin(Vector3D origin);

        /**
         * Sets the direction of this Ray3D to the given direction. The direction will
         * be normalized.
         * @param direction the new direction to set this Ray3D to.
         */
        void setDirection(Vector3D direction);

        /**
         * Determines if the given Vector3D, interpreted as a point, lies on this Ray3D.
         * @param point the Vector3D point to check if it lies on this Ray3D.
         */
        bool isPointOn(Vector3D point) const;

        /**
         * Overriden << operator to allow easy printing of this Ray3D object.
         * 
         * The returned stream will be in the format of 
         * `Ray3D(Origin=<origin>, direction=<direction>)`
         * Where `<origin>` and `<direction>` are the streams returned by the
         * overridden << operator in Vector3D.
         */
        friend std::ostream& operator<<(std::ostream &stream, const Ray3D& r);
};


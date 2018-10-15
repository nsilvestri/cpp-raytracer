#pragma once

#include "Vector3D.hpp"
#include "Surface.hpp"

class Surface; // forward declaration
typedef struct IntersectionRecord
{
    Surface* surfaceIntersected;
    Vector3D pointOfIntersection;
    Vector3D normalAtIntersection;
    float t;
} IntersectionRecord;
#include "catch.hpp"

#include "../Sphere.hpp"
#include "../Vector3D.hpp"
#include "../Ray3D.hpp"
#include "../IntersectionRecord.hpp"

TEST_CASE("Test intersection", "[Sphere]")
{
    Sphere s = Sphere(Vector3D(0, 0, 0), 1);
    IntersectionRecord ir;

    Ray3D alongX = Ray3D(Vector3D(100, 0, 0), Vector3D(0, 0, 0));
    Ray3D alongY = Ray3D(Vector3D(0, 100, 0), Vector3D(0, 0, 0));
    Ray3D alongZ = Ray3D(Vector3D(0, 0, 100), Vector3D(0, 0, 0));
    Ray3D miss = Ray3D(Vector3D(100, 100, 100), Vector3D(1000, 1000, 1000));

    REQUIRE(s.intersect(ir, alongX));
    REQUIRE(s.intersect(ir, alongY));
    REQUIRE(s.intersect(ir, alongZ));
    REQUIRE(!s.intersect(ir, miss));
}
#include "catch.hpp"

#include "../Sphere.hpp"
#include "../Vector3D.hpp"
#include "../Ray3D.hpp"
#include "../IntersectionRecord.hpp"

TEST_CASE("Test intersection", "[Sphere]")
{
    Sphere s = Sphere(Vector3D(0, 0, 0), 1);
    IntersectionRecord ir;

    Ray3D alongX = Ray3D(Vector3D(-100, 0, 0), Vector3D(1, 0, 0));
    REQUIRE(s.intersect(ir, alongX));
    REQUIRE(ir.normalAtIntersection == Vector3D(-1, 0, 0));
    REQUIRE(ir.normalAtIntersection != Vector3D(-1, 5, 0));
    REQUIRE(ir.pointOfIntersection == Vector3D(-1, 0, 0));
    REQUIRE(ir.pointOfIntersection != Vector3D(-1, 5, 0));


    Ray3D alongY = Ray3D(Vector3D(0, 100, 0), Vector3D(0, 1, 0));
    Ray3D alongZ = Ray3D(Vector3D(0, 0, 100), Vector3D(0, 0, 1));
    Ray3D graze = Ray3D(Vector3D(-1, 1, 0), Vector3D(1, 0, 0));
    Ray3D miss = Ray3D(Vector3D(-10, 10, 0), Vector3D(0, 1, 0));

    REQUIRE(s.intersect(ir, alongY));
    REQUIRE(s.intersect(ir, alongZ));
    REQUIRE(s.intersect(ir, graze));
    REQUIRE(!s.intersect(ir, miss));

    Ray3D throughOrigin = Ray3D(Vector3D(1, 1, 1), Vector3D(-1, -1, -1));
    REQUIRE(s.intersect(ir, throughOrigin));
}
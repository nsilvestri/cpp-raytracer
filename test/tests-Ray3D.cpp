#include "catch.hpp"

#include "../Vector3D.hpp"
#include "../Ray3D.hpp"

TEST_CASE("Test point lying on ray", "[Ray3D]")
{
    Ray3D r = Ray3D(Vector3D(0, 0, 0), Vector3D(1, 0, 0));

    REQUIRE(r.isPointOn(Vector3D(1, 0, 0)));
    REQUIRE(r.isPointOn(Vector3D(99, 0, 0)));
    REQUIRE(r.isPointOn(Vector3D(.5, 0, 0)));
    REQUIRE(r.isPointOn(Vector3D(-1, 0, 0)));
}
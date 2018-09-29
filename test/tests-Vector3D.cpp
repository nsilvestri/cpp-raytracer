#include "catch.hpp"

#include "../Vector3D.hpp"

TEST_CASE("Scale vector by scalar", "[Vector3D]")
{
    Vector3D v(1, 2, 3);
    v = v * 2.0;
    REQUIRE(v.getX() == 2);
    REQUIRE(v.getY() == 4);
    REQUIRE(v.getZ() == 6);

    v = v * -4.0;
    REQUIRE(v.getX() == -8);
    REQUIRE(v.getY() == -16);
    REQUIRE(v.getZ() == -24);
}

TEST_CASE("Add two vectors", "[Vector3D]")
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 3, 5);

    Vector3D v3 = v1 + v2;
    REQUIRE(v3.getX() == 2);
    REQUIRE(v3.getY() == 5);
    REQUIRE(v3.getZ() == 8);
}

TEST_CASE("Dot two vectors", "[Vector3D]")
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 3, 5);

    REQUIRE(v1.dot(v2) == 22);
    REQUIRE(v2.dot(v1) == 22);
}

TEST_CASE("Cross product of two vectors", "[Vector3D]")
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 3, 5);
    Vector3D v3;
    
    v3 = v1.cross(v2);
    REQUIRE(v3.getX() == 1);
    REQUIRE(v3.getY() == -2);
    REQUIRE(v3.getZ() == 1);

    v3 = v2.cross(v1);
    REQUIRE(v3.getX() == -1);
    REQUIRE(v3.getY() == 2);
    REQUIRE(v3.getZ() == -1);
}
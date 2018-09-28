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

    float d = v1.dot(v2);
    REQUIRE(d == 22);
}
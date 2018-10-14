#include <math.h>

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

TEST_CASE("Subtract two vectors", "[Vector3D]")
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(1, 3, 5);

    Vector3D v3 = v1 - v2;
    REQUIRE(v3.getX() == 0);
    REQUIRE(v3.getY() == -1);
    REQUIRE(v3.getZ() == -2);
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

TEST_CASE("Calculate the length of a vector", "[Vector3D]")
{   
    Vector3D v0(0, 0, 0);
    REQUIRE(v0.length() == 0);
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);
    Vector3D v3(0, 0, 1);
    Vector3D v4(-1, 0, 0);
    Vector3D v5(0, -1, 0);
    Vector3D v6(0, 0, -1);
    REQUIRE(v1.length() == 1);
    REQUIRE(v2.length() == 1);
    REQUIRE(v3.length() == 1);
    REQUIRE(v4.length() == 1);
    REQUIRE(v5.length() == 1);
    REQUIRE(v6.length() == 1);

    Approx sqrt3 = Approx(sqrt(3)).margin(0.01);
    Vector3D v7(1, 1, 1);
    Vector3D v8(1, -1, 1);
    REQUIRE(v7.length() == sqrt3);
    REQUIRE(v8.length() == sqrt3);
}

TEST_CASE("Normalize vector", "[Vector3D]")
{
    Approx one = Approx(sqrt(1)).margin(0.01);

    Vector3D v1(1, 2, 3);
    v1.normalize();
    REQUIRE(v1.length() == one);

    Vector3D v2(2359, -222, 6820);
    v2.normalize();
    REQUIRE(v2.length() == one);

    Vector3D v3(-35, 0, 0.13);
    v3.normalize();
    REQUIRE(v3.length() == one);

    Vector3D v4(0, 0, 0);
    v4.normalize();
    REQUIRE(v4.length() == 0.0);
}

TEST_CASE("Test equality operator", "[Vector3D]")
{
    Vector3D v1 = Vector3D(1, 2, 3);
    Vector3D v2 = Vector3D(1, 2, 3);   
    Vector3D v3 = Vector3D(-3, 0, 1);
    REQUIRE(v1 == v1);
    REQUIRE(v1 == v2);
    REQUIRE(v2 != v3);
}
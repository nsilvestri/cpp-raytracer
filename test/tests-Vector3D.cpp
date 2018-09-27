#include "catch.hpp"

#include "../Vector3D.hpp"

TEST_CASE("Scale vector by scalar", "[Vector3D]")
{
    Vector3D* v = new Vector3D(1, 2, 3);

    Vector3D v1 = *v;
    v1 = v1 * 2.0;
    REQUIRE(v->getX() == 2);
}
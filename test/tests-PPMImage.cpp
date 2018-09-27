#include "catch.hpp"
#include "../RGBColor.hpp"
#include "../PPMImage.hpp"

TEST_CASE("Get specific pixel", "[PPMImage]")
{
    RGBColor* pixels = new RGBColor[9];

    for (int i = 0; i < 9; i++)
    {
        RGBColor* p = new RGBColor(i / 10.0, i / 10.0, i / 10.0);
        pixels[i] = *p;
    }

    PPMImage* i = new PPMImage(pixels, 3, 3);

    Approx target1 = Approx(0).margin(0.01);
    REQUIRE(i->getPixelAt(0, 0).getR() == target1);

    Approx target2 = Approx(.1).epsilon(0.01);
    REQUIRE(i->getPixelAt(0, 1).getG() == target2);

    Approx target3 = Approx(.8).epsilon(0.01);
    REQUIRE(i->getPixelAt(2, 2).getB() == target3);
}
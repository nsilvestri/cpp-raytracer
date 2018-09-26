#include "catch.hpp"

#include "../RGBPixel.hpp"

TEST_CASE("Compute pixel luminance", "[RGBPixel]")
{
    RGBPixel* p = new RGBPixel(0, 0, 0);

    REQUIRE(p->getLuminance() == 0);

    p->setRGB(1, 1, 1);

    REQUIRE(p->getLuminance() == 1);
}

TEST_CASE("Scale pixel", "[RGBPixel]")
{
    RGBPixel* p = new RGBPixel(0, 0, 0);

    p->scale(0);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == 0);
    REQUIRE(p->getB() == 0);
    
    p->scale(1);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == 0);
    REQUIRE(p->getB() == 0);

    p->scale(4);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == 0);
    REQUIRE(p->getB() == 0);

    // test clamping
    p->setRGB(1, 1, 1);

    p->scale(1);
    REQUIRE(p->getR() == 1);
    REQUIRE(p->getG() == 1);
    REQUIRE(p->getB() == 1);
    
    p->scale(2.65);
    REQUIRE(p->getR() == 1);
    REQUIRE(p->getG() == 1);
    REQUIRE(p->getB() == 1);

    p->scale(-15);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == 0);
    REQUIRE(p->getB() == 0);
}

TEST_CASE("Test channel getters", "[RGBPixel]")
{
    RGBPixel* p = new RGBPixel(0, .5, 1);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == .5);
    REQUIRE(p->getB() == 1);
}

TEST_CASE("Test setters", "[RGBPixel]")
{
    RGBPixel* p = new RGBPixel(0, .5, 1);
    
    p->setR(1);
    p->setG(0);
    p->setB(.5);
    REQUIRE(p->getR() == 1);
    REQUIRE(p->getG() == 0);
    REQUIRE(p->getB() == .5);

    p->setRGB(0, .5, 1);
    REQUIRE(p->getR() == 0);
    REQUIRE(p->getG() == .5);
    REQUIRE(p->getB() == 1);
}

TEST_CASE("Test clamping", "[RGBPixel]")
{
    REQUIRE(RGBPixel::clamp(.5) == .5);
    REQUIRE(RGBPixel::clamp(0) == 0);
    REQUIRE(RGBPixel::clamp(1) == 1);

    REQUIRE(RGBPixel::clamp(-1) == 0);
    REQUIRE(RGBPixel::clamp(2) == 1);
}
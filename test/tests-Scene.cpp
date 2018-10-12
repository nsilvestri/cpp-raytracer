#include "catch.hpp"
#include "../Scene.hpp"

TEST_CASE("Test reading in scene file", "[Scene.cpp]")
{ 
    Scene s = Scene();
    s.readSceneFile("../scenes/1sphere433.txt");
}
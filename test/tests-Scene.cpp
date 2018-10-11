#include "catch.hpp"
#include "../Scene.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

TEST_CASE("Test reading in scene file", "[Scene.cpp]")
{
    spdlog::set_level(spdlog::level::debug);   
    Scene s = Scene();
    s.readSceneFile("../scenes/1sphere433.txt");
}
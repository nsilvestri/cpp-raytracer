cmake_minimum_required(VERSION 2.8.11)
project(prog03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(SDL2)

set(source_files
  main.cpp
  easylogging++.cc
  
  PPMImage.cpp
  RGBColor.cpp
  Material.cpp

  Scene.cpp
  Camera.cpp

  Vector3D.cpp
  Ray3D.cpp

  Surface.cpp
  Sphere.cpp
  Plane.cpp
  Light.cpp
)

message(${SDL2_INCLUDE_DIR})
message(${SDL2_LIBRARY})

include_directories(
  ${SDL2_INCLUDE_DIR}
)

add_executable(
  ${PROJECT_NAME}
  ${source_files}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${SDL2_LIBRARY}
)


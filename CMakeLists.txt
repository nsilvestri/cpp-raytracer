cmake_minimum_required(VERSION 2.8.11)
project(prog03)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
  endif ()
endmacro(use_cxx11)
use_cxx11()
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


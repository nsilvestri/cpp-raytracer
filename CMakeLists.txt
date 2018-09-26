cmake_minimum_required(VERSION 2.8.11)
project(prog03)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2)

set(source_files
  main.cpp
  PPMImage.cpp
  RGBPixel.cpp
)

include_directories (${SDL2_INCLUDE_DIR})
add_executable (${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})


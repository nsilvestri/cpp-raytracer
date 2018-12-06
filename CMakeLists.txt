cmake_minimum_required(VERSION 2.8.11)
project(raytracer)

# CMake 2.8 and 3.1 compatibility

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

# SDL2
find_package(SDL2)
# set(SDL2_LIBRARY /usr/lib/libSDL2.so)
message(${SDL2_INCLUDE_DIR})
message(${SDL2_LIBRARY})

include_directories(
  ${SDL2_INCLUDE_DIR}
)

# find packages

# includes
include_directories(
  include
)

# find header & source
file(GLOB_RECURSE HEADER "include/*.hpp")
file(GLOB_RECURSE SOURCE "src/*.cpp")

add_executable(${PROJECT_NAME}
  ${SOURCE}
  ${HEADER}
)

source_group("Header include" FILES ${HEADER})
source_group("Source src"     FILES ${SOURCE})

target_link_libraries(
  ${PROJECT_NAME}
  ${SDL2_LIBRARY}
)


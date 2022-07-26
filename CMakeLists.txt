# Set up the minimum version of cmake
cmake_minimum_required(VERSION 3.10.0)

# Set the project name and version
set(PROJECT_NAME "Engine")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_REVISION 0)

project(${PROJECT_NAME})

message("Building ${PROJECT_NAME}...")

option(BUILD_TESTS "Building the engine tests" OFF)

# Set the C++ standard to be used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add customs Flags
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Werror -Wfatal-errors -O0 -g -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Werror -Wfatal-errors -O3 -s -fexpensive-optimizations")

# CMake options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Set default build type explicitly to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build type." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(SOURCES
    sources/Common/Maths.cpp
    sources/Common/String.cpp

    sources/Geometry/Bounds.cpp
    sources/Geometry/Collision.cpp
    sources/Geometry/Geometry.cpp
    sources/Geometry/Vector.cpp
    sources/Geometry/Vertices.cpp

    sources/Benchmark/BlockData.cpp
    sources/Benchmark/Performance.cpp
    sources/Benchmark/Recorder.cpp

    sources/Corpses/Circle.cpp
    sources/Corpses/Corpse.cpp
    sources/Corpses/Polygon.cpp

    sources/Constraints/Constraint.cpp
    sources/Constraints/Link.cpp
    sources/Constraints/Loose.cpp
    sources/Constraints/Motor.cpp
    sources/Constraints/Propulsor.cpp
    sources/Constraints/Slider.cpp
    sources/Constraints/Spring.cpp

    sources/Structures/QuadTree.cpp
    sources/Structures/QuadNode.cpp
    sources/Structures/System.cpp
)

set(HEADERS
    include/Common/Maths.hpp
    include/Common/String.hpp

    include/Geometry/Bounds.hpp
    include/Geometry/Collision.hpp
    include/Geometry/Geometry.hpp
    include/Geometry/Vector.hpp
    include/Geometry/Vertices.hpp

    include/Benchmark/BlockData.hpp
    include/Benchmark/Performance.hpp
    include/Benchmark/Recorder.hpp

    include/Corpses/Circle.hpp
    include/Corpses/Corpse.hpp
    include/Corpses/Polygon.hpp

    include/Constraints/Constraint.hpp
    include/Constraints/Link.hpp
    include/Constraints/Loose.hpp
    include/Constraints/Motor.hpp
    include/Constraints/Propulsor.hpp
    include/Constraints/Slider.hpp
    include/Constraints/Spring.hpp

    include/Structures/QuadTree.hpp
    include/Structures/QuadNode.hpp
    include/Structures/System.hpp
)

configure_file("${PROJECT_SOURCE_DIR}/Config.hpp.in" "${PROJECT_BINARY_DIR}/Config.hpp")
include_directories("${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
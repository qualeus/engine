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

set(HEADERS
    include/Benchmark/BlockData.hpp
    include/Benchmark/Performance.hpp
    include/Benchmark/Recorder.hpp

    include/Common/Maths.hpp
    include/Common/String.hpp

    include/Constraints/Constraint.hpp
    include/Constraints/Link.hpp

    include/Collisions/Collision.hpp

    include/Corpses/Circle.hpp
    include/Corpses/Corpse.hpp
    include/Corpses/Edge.hpp
    include/Corpses/Polygon.hpp
    include/Corpses/Shape.hpp

    include/Geometry/Bounds.hpp
    include/Geometry/Geometry.hpp
    include/Geometry/Matrix2.hpp
    include/Geometry/Vector2.hpp
    include/Geometry/Vertices2.hpp

    include/Integrators/Euler.hpp
    include/Integrators/Integrator.hpp
    include/Integrators/Verlet.hpp

    include/Partitioners/Bounding.hpp
    include/Partitioners/BruteForce.hpp
    include/Partitioners/KDTree.hpp
    include/Partitioners/Partitioner.hpp
    include/Partitioners/QuadTree.hpp
    include/Partitioners/SpatialGrid.hpp

    include/Solvers/Sequential.hpp
    include/Solvers/Solver.hpp

    include/System/System.hpp
)

set(SOURCES
    sources/Benchmark/BlockData.cpp
    sources/Benchmark/Performance.cpp
    sources/Benchmark/Recorder.cpp

    sources/Common/Maths.cpp
    sources/Common/String.cpp

    sources/Constraints/Constraint.cpp
    sources/Constraints/Link.cpp

    sources/Collisions/Collision.cpp

    sources/Corpses/Circle.cpp
    sources/Corpses/Corpse.cpp
    sources/Corpses/Edge.cpp
    sources/Corpses/Polygon.cpp
    sources/Corpses/Shape.cpp

    sources/Geometry/Bounds.cpp
    sources/Geometry/Geometry.cpp
    sources/Geometry/Matrix2.cpp
    sources/Geometry/Vector2.cpp
    sources/Geometry/Vertices2.cpp

    sources/Integrators/Euler.cpp
    sources/Integrators/Integrator.cpp
    sources/Integrators/Verlet.cpp

    sources/Partitioners/Bounding.cpp
    sources/Partitioners/BruteForce.cpp
    sources/Partitioners/KDTree.cpp
    sources/Partitioners/Partitioner.cpp
    sources/Partitioners/QuadTree.cpp
    sources/Partitioners/SpatialGrid.cpp

    sources/Solvers/Sequential.cpp
    sources/Solvers/Solver.cpp

    sources/System/System.cpp
)

configure_file("${PROJECT_SOURCE_DIR}/Config.hpp.in" "${PROJECT_BINARY_DIR}/Config.hpp")
include_directories("${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
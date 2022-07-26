# Set up the minimum version of cmake
cmake_minimum_required(VERSION 3.10.0)

enable_testing()
project("Engine tests")

message("Building tests...")

# Set the C++ standard to be used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Debug")

# Add customs Flags
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Werror -Wfatal-errors")

set(LIBRARIES_PATH "")

# CMake options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB TESTS_DIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(test ${TESTS_DIR})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test})

    set_target_properties(${testName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    target_link_libraries(${testName} Engine)
    add_test(${testName} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${testName})
endforeach(test)
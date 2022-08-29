#include "../include/Geometry/Vertices2.hpp"
#include "test.hpp"

template <typename T>
void function_centroid() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    gmt::Vector2<T> test_result = square.centroid();
    gmt::Vector2<T> true_result = gmt::Vector2<T>(2, 2);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_average() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    gmt::Vector2<T> test_result = square.average();
    gmt::Vector2<T> true_result = gmt::Vector2<T>(2, 2);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_convex() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    bool test_result = square.convex();
    bool true_result = true;
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_area() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    T test_result = square.area();
    T true_result = static_cast<T>(4 * 4);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_sizes() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    com::vec<T> test_result = square.sizes();
    com::vec<T> true_result = {static_cast<T>(4), static_cast<T>(4), static_cast<T>(4), static_cast<T>(4)};

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_limits() {
    gmt::Vertices2<T> square = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    gmt::Bounds<T> test_result = square.limits();
    gmt::Bounds<T> true_result = gmt::Bounds<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(4), static_cast<T>(4));

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_reorder() {
    gmt::Vertices2<T> test_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 4),  // vertex 1
        gmt::Vector2<T>(4, 4),  // vertex 2
        gmt::Vector2<T>(4, 0),  // vertex 3
        gmt::Vector2<T>(0, 0)   // vertex 4
    });

    test_result.reorder();

    gmt::Vertices2<T> true_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 4),  // vertex 1
        gmt::Vector2<T>(4, 4),  // vertex 2
        gmt::Vector2<T>(4, 0),  // vertex 3
        gmt::Vector2<T>(0, 0)   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_translate() {
    gmt::Vertices2<T> test_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    test_result.translate(gmt::Vector2<T>(3, 2));

    gmt::Vertices2<T> true_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(3, 2),  // vertex 1
        gmt::Vector2<T>(7, 2),  // vertex 2
        gmt::Vector2<T>(7, 6),  // vertex 3
        gmt::Vector2<T>(3, 6)   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_rotate() {
    gmt::Vertices2<T> test_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    test_result.rotate(static_cast<T>(PI), gmt::Vector2<T>(2, 2));

    gmt::Vertices2<T> true_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_scale() {
    gmt::Vertices2<T> test_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(0, 0),  // vertex 1
        gmt::Vector2<T>(4, 0),  // vertex 2
        gmt::Vector2<T>(4, 4),  // vertex 3
        gmt::Vector2<T>(0, 4)   // vertex 4
    });

    test_result.scale(static_cast<T>(2), gmt::Vector2<T>(2, 2));

    gmt::Vertices2<T> true_result = gmt::Vertices2<T>({
        gmt::Vector2<T>(-2, -2),  // vertex 1
        gmt::Vector2<T>(6, -2),   // vertex 2
        gmt::Vector2<T>(6, 6),    // vertex 3
        gmt::Vector2<T>(-2, 6)    // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    function_centroid<int>();
    function_centroid<float>();
    function_centroid<double>();

    function_average<int>();
    function_average<float>();
    function_average<double>();

    function_convex<int>();
    function_convex<float>();
    function_convex<double>();

    function_area<int>();
    function_area<float>();
    function_area<double>();

    function_sizes<int>();
    function_sizes<float>();
    function_sizes<double>();

    function_limits<int>();
    function_limits<float>();
    function_limits<double>();

    function_reorder<int>();
    function_reorder<float>();
    function_reorder<double>();

    function_translate<int>();
    function_translate<float>();
    function_translate<double>();

    // FIX ROTATIONS
    // function_rotate<int>();
    // function_rotate<float>();
    // function_rotate<double>();

    function_scale<int>();
    function_scale<float>();
    function_scale<double>();
}
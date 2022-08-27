#include "test.hpp"

template <typename T>
void operator_plus() {
    gmt::Vector2<T> lhs = gmt::Vector2<T>(1, 2);
    gmt::Vector2<T> rhs = gmt::Vector2<T>(1, 3);

    gmt::Vector2<T> test_result = lhs + rhs;
    gmt::Vector2<T> true_result = gmt::Vector2<T>(2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + lhs;
    true_result = gmt::Vector2<T>(2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + rhs;
    true_result = gmt::Vector2<T>(2, 6);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_minus() {
    gmt::Vector2<T> lhs = gmt::Vector2<T>(1, 2);
    gmt::Vector2<T> rhs = gmt::Vector2<T>(1, 3);

    gmt::Vector2<T> test_result = lhs - rhs;
    gmt::Vector2<T> true_result = gmt::Vector2<T>(0, -1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - lhs;
    true_result = gmt::Vector2<T>(0, 1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - rhs;
    true_result = gmt::Vector2<T>(0, 0);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_dot() {
    T test_result = gmt::Vector2<T>::dot(gmt::Vector2<T>(), gmt::Vector2<T>());
    T true_result = T(0);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::dot(gmt::Vector2<T>(15, 7), gmt::Vector2<T>(4, 78));
    true_result = T(606);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::dot(gmt::Vector2<T>(84, 14), gmt::Vector2<T>(878, 1105));
    true_result = T(89222);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::dot(gmt::Vector2<T>(-15, -45), gmt::Vector2<T>(-12, 0));
    true_result = T(180);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_cross() {
    T test_result = gmt::Vector2<T>::cross(gmt::Vector2<T>(), gmt::Vector2<T>());
    T true_result = T(0);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::cross(gmt::Vector2<T>(15, 7), gmt::Vector2<T>(4, 78));
    true_result = T(1142);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::cross(gmt::Vector2<T>(84, 14), gmt::Vector2<T>(878, 1105));
    true_result = T(80528);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector2<T>::cross(gmt::Vector2<T>(-15, -45), gmt::Vector2<T>(-12, 0));
    true_result = T(-540);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_segment_projection() {
    gmt::Vector2<T> test_result = gmt::Vector2<T>::segment_projection(gmt::Vector2<T>(4, 3), gmt::Vector2<T>(0, 0), gmt::Vector2<T>(4, 0));
    gmt::Vector2<T> true_result = gmt::Vector2<T>(4, 0);
    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    operator_plus<int>();
    operator_plus<float>();
    operator_plus<double>();

    operator_minus<int>();
    operator_minus<float>();
    operator_minus<double>();

    function_dot<int>();
    function_dot<float>();
    function_dot<double>();

    function_cross<int>();
    function_cross<float>();
    function_cross<double>();

    function_segment_projection<int>();
    function_segment_projection<float>();
    function_segment_projection<double>();
}
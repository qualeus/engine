#include "../include/Geometry/Matrix2.hpp"
#include "test.hpp"

template <typename T>
void operator_subscript() {
    gmt::Matrix2<T> test_result = gmt::Matrix2<T>(1, 2, 1, 2);
    std::vector<T> true_result  = {1, 2, 1, 2};

    for (int i = 0; i < 4; i++) { ASSERT_EQUAL(true_result[i], test_result[i]); }
}

template <typename T>
void operator_plus() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 1, 2);
    gmt::Matrix2<T> rhs = gmt::Matrix2<T>(1, 3, 1, 3);

    gmt::Matrix2<T> test_result = lhs + rhs;
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(2, 5, 2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + lhs;
    true_result = gmt::Matrix2<T>(2, 5, 2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + rhs;
    true_result = gmt::Matrix2<T>(2, 6, 2, 6);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_minus() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 1, 2);
    gmt::Matrix2<T> rhs = gmt::Matrix2<T>(1, 3, 1, 3);

    gmt::Matrix2<T> test_result = lhs - rhs;
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(0, -1, 0, -1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - lhs;
    true_result = gmt::Matrix2<T>(0, 1, 0, 1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - rhs;
    true_result = gmt::Matrix2<T>(0, 0, 0, 0);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_time_scalar() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 1, 2);

    gmt::Matrix2<T> test_result = lhs * T(3);
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(3, 6, 3, 6);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * T(-1);
    true_result = gmt::Matrix2<T>(-1, -2, -1, -2);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * T(10);
    true_result = gmt::Matrix2<T>(10, 20, 10, 20);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_divided_scalar() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(2, 4, 2, 2);

    gmt::Matrix2<T> test_result = lhs / T(2);
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(1, 2, 1, 1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs / T(1);
    true_result = gmt::Matrix2<T>(2, 4, 2, 2);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs / T(-1);
    true_result = gmt::Matrix2<T>(-2, -4, -2, -2);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_time_vector() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 1, 2);
    gmt::Vector2<T> rhs = gmt::Vector2<T>(3, 4);

    gmt::Vector2<T> test_result = lhs * rhs;
    gmt::Vector2<T> true_result = gmt::Vector2<T>(11, 11);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * -rhs;
    true_result = gmt::Vector2<T>(-11, -11);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * (rhs * T(2));
    true_result = gmt::Vector2<T>(22, 22);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_time_matrix() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 3, 4);
    gmt::Matrix2<T> rhs = gmt::Matrix2<T>(3, 4, 6, 8);

    gmt::Matrix2<T> test_result = lhs * rhs;
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(15, 20, 33, 44);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * (rhs * T(-1));
    true_result = gmt::Matrix2<T>(-15, -20, -33, -44);
    ASSERT_EQUAL(true_result, test_result);

    test_result = lhs * (rhs * T(2));
    true_result = gmt::Matrix2<T>(30, 40, 66, 88);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_transpose() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(1, 2, 3, 4);

    gmt::Matrix2<T> test_result = lhs.transpose();
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(1, 3, 2, 4);

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_determinant() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(3, 7, 2, 3);

    T test_result = lhs.determinant();
    T true_result = T(-5);

    ASSERT_EQUAL(true_result, test_result);

    lhs = gmt::Matrix2<T>(5, 3, 3, 2);

    test_result = lhs.determinant();
    true_result = T(1);

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void function_invert() {
    gmt::Matrix2<T> lhs = gmt::Matrix2<T>(5, 3, 3, 2);

    gmt::Matrix2<T> test_result = lhs.invert();
    gmt::Matrix2<T> true_result = gmt::Matrix2<T>(2, -3, -3, 5);

    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    operator_subscript<int>();
    operator_subscript<float>();
    operator_subscript<double>();

    operator_plus<int>();
    operator_plus<float>();
    operator_plus<double>();

    operator_minus<int>();
    operator_minus<float>();
    operator_minus<double>();

    operator_time_scalar<int>();
    operator_time_scalar<float>();
    operator_time_scalar<double>();

    operator_divided_scalar<int>();
    operator_divided_scalar<float>();
    operator_divided_scalar<double>();

    operator_time_vector<int>();
    operator_time_vector<float>();
    operator_time_vector<double>();

    operator_time_matrix<int>();
    operator_time_matrix<float>();
    operator_time_matrix<double>();

    function_transpose<int>();
    function_transpose<float>();
    function_transpose<double>();

    function_determinant<int>();
    function_determinant<float>();
    function_determinant<double>();

    function_invert<int>();
    function_invert<float>();
    function_invert<double>();
}
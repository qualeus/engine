#include "test.hpp"

template <typename T>
void operator_plus() {
    gmt::Bounds<T> lhs = gmt::Bounds<T>(0, 0, 10, 10);
    gmt::Bounds<T> rhs = gmt::Bounds<T>(0, 10, 10, 20);

    gmt::Bounds<T> test_result = lhs + rhs;
    gmt::Bounds<T> true_result = gmt::Bounds<T>(0, 10, 20, 30);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + lhs;
    true_result = gmt::Bounds<T>(0, 10, 20, 30);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + rhs;
    true_result = true_result = gmt::Bounds<T>(0, 20, 20, 40);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void operator_minus() {
    gmt::Bounds<T> lhs = gmt::Bounds<T>(0, 0, 10, 10);
    gmt::Bounds<T> rhs = gmt::Bounds<T>(0, 10, 10, 20);

    gmt::Bounds<T> test_result = lhs - rhs;
    gmt::Bounds<T> true_result = gmt::Bounds<T>(0, -10, 0, -10);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - lhs;
    true_result = gmt::Bounds<T>(0, 10, 0, 10);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - rhs;
    true_result = true_result = gmt::Bounds<T>(0, 0, 0, 0);
    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    operator_plus<int>();
    operator_plus<float>();
    operator_plus<double>();

    operator_minus<int>();
    operator_minus<float>();
    operator_minus<double>();
}
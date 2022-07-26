#include "test.hpp"

template <typename T>
void OperatorPlus() {
    gmt::Vector<T> lhs = gmt::Vector<T>(1, 2);
    gmt::Vector<T> rhs = gmt::Vector<T>(1, 3);

    gmt::Vector<T> test_result = lhs + rhs;
    gmt::Vector<T> true_result = gmt::Vector<T>(2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + lhs;
    true_result = gmt::Vector<T>(2, 5);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs + rhs;
    true_result = gmt::Vector<T>(2, 6);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void OperatorMinus() {
    gmt::Vector<T> lhs = gmt::Vector<T>(1, 2);
    gmt::Vector<T> rhs = gmt::Vector<T>(1, 3);

    gmt::Vector<T> test_result = lhs - rhs;
    gmt::Vector<T> true_result = gmt::Vector<T>(0, -1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - lhs;
    true_result = gmt::Vector<T>(0, 1);
    ASSERT_EQUAL(true_result, test_result);

    test_result = rhs - rhs;
    true_result = gmt::Vector<T>(0, 0);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionDot() {
    T test_result = gmt::Vector<T>::Dot(gmt::Vector<T>(), gmt::Vector<T>());
    T true_result = T(0);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Dot(gmt::Vector<T>(15, 7), gmt::Vector<T>(4, 78));
    true_result = T(606);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Dot(gmt::Vector<T>(84, 14), gmt::Vector<T>(878, 1105));
    true_result = T(89222);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Dot(gmt::Vector<T>(-15, -45), gmt::Vector<T>(-12, 0));
    true_result = T(180);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionCross() {
    T test_result = gmt::Vector<T>::Cross(gmt::Vector<T>(), gmt::Vector<T>());
    T true_result = T(0);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Cross(gmt::Vector<T>(15, 7), gmt::Vector<T>(4, 78));
    true_result = T(1142);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Cross(gmt::Vector<T>(84, 14), gmt::Vector<T>(878, 1105));
    true_result = T(80528);
    ASSERT_EQUAL(true_result, test_result);

    test_result = gmt::Vector<T>::Cross(gmt::Vector<T>(-15, -45), gmt::Vector<T>(-12, 0));
    true_result = T(-540);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionSegmentProjection() {
    gmt::Vector<T> test_result = gmt::Vector<T>::SegmentProjection(gmt::Vector<T>(4, 3), gmt::Vector<T>(0, 0), gmt::Vector<T>(4, 0));
    gmt::Vector<T> true_result = gmt::Vector<T>(4, 0);
    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    OperatorPlus<int>();
    OperatorPlus<float>();
    OperatorPlus<double>();

    OperatorMinus<int>();
    OperatorMinus<float>();
    OperatorMinus<double>();

    FunctionDot<int>();
    FunctionDot<float>();
    FunctionDot<double>();

    FunctionCross<int>();
    FunctionCross<float>();
    FunctionCross<double>();

    FunctionSegmentProjection<int>();
    FunctionSegmentProjection<float>();
    FunctionSegmentProjection<double>();
}
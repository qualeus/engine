#include "test.hpp"

template <typename T>
void FunctionCentroid() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    gmt::Vector<T> test_result = square.Centroid();
    gmt::Vector<T> true_result = gmt::Vector<T>(2, 2);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionAverage() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    gmt::Vector<T> test_result = square.Average();
    gmt::Vector<T> true_result = gmt::Vector<T>(2, 2);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionConvex() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    bool test_result = square.Convex();
    bool true_result = true;
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionArea() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    T test_result = square.Area();
    T true_result = static_cast<T>(4 * 4);
    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionSizes() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    std::vector<T> test_result = square.Sizes();
    std::vector<T> true_result = {static_cast<T>(4), static_cast<T>(4), static_cast<T>(4), static_cast<T>(4)};

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionLimits() {
    gmt::Vertices<T> square = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    gmt::Bounds<T> test_result = square.Limits();
    gmt::Bounds<T> true_result = gmt::Bounds<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(4), static_cast<T>(4));

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionReorder() {
    gmt::Vertices<T> test_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0))   // vertex 4
    });

    test_result.Reorder();

    gmt::Vertices<T> true_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0))   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionTranslate() {
    gmt::Vertices<T> test_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    test_result.Translate(gmt::Vector<T>(3, 2));

    gmt::Vertices<T> true_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(3, 2)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(7, 2)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(7, 6)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(3, 6))   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionRotate() {
    gmt::Vertices<T> test_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    test_result.Rotate(static_cast<T>(PI), gmt::Vector<T>(2, 2));

    gmt::Vertices<T> true_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

template <typename T>
void FunctionScale() {
    gmt::Vertices<T> test_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 0)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 0)),  // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(4, 4)),  // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(0, 4))   // vertex 4
    });

    test_result.Scale(static_cast<T>(2), gmt::Vector<T>(2, 2));

    gmt::Vertices<T> true_result = gmt::Vertices<T>({
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(-2, -2)),  // vertex 1
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(6, -2)),   // vertex 2
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(6, 6)),    // vertex 3
        std::make_shared<gmt::Vector<T>>(gmt::Vector<T>(-2, 6))    // vertex 4
    });

    ASSERT_EQUAL(true_result, test_result);
}

int main() {
    FunctionCentroid<int>();
    FunctionCentroid<float>();
    FunctionCentroid<double>();

    FunctionAverage<int>();
    FunctionAverage<float>();
    FunctionAverage<double>();

    FunctionConvex<int>();
    FunctionConvex<float>();
    FunctionConvex<double>();

    FunctionArea<int>();
    FunctionArea<float>();
    FunctionArea<double>();

    FunctionSizes<int>();
    FunctionSizes<float>();
    FunctionSizes<double>();

    FunctionLimits<int>();
    FunctionLimits<float>();
    FunctionLimits<double>();

    FunctionReorder<int>();
    FunctionReorder<float>();
    FunctionReorder<double>();

    FunctionTranslate<int>();
    FunctionTranslate<float>();
    FunctionTranslate<double>();

    // FIX ROTATIONS
    // FunctionRotate<int>();
    // FunctionRotate<float>();
    // FunctionRotate<double>();

    FunctionScale<int>();
    FunctionScale<float>();
    FunctionScale<double>();
}
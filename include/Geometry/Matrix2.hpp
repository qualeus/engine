#ifndef Matrix2_HPP
#define Matrix2_HPP

#include "../Common/Maths.hpp"
#include "../Common/String.hpp"
#include "Vector2.hpp"

namespace gmt {

template <typename T>
class Matrix2 {
   public:
    com::arr<T, 4> m_data;

    Matrix2();
    Matrix2(const T& x, const T& y, const T& z, const T& w);

    T operator[](int index) const;
    T get(int i, int j) const;

    Matrix2<T> operator+(const Matrix2<T>& other) const;
    Matrix2<T> operator-(const Matrix2<T>& other) const;

    Matrix2<T> operator*(const T& other) const;
    Matrix2<T> operator/(const T& other) const;

    Vector2<T> operator*(const Vector2<T>& other) const;
    Vector2<T> operator/(const Vector2<T>& other) const;

    Matrix2<T> operator*(const Matrix2<T>& other) const;
    Matrix2<T> operator/(const Matrix2<T>& other) const;

    T determinant() const;
    Matrix2<T> transpose() const;
    Matrix2<T> invert() const;
};

}  // namespace gmt

#endif
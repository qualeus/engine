#include "../../include/Geometry/Matrix2.hpp"

namespace gmt {

/* Default Constructor */
template <typename T>
Matrix2<T>::Matrix2() {
    m_data = {T(0), T(0), T(0), T(0)};
}
template Matrix2<int>::Matrix2();
template Matrix2<float>::Matrix2();
template Matrix2<double>::Matrix2();

template <typename T>
Matrix2<T>::Matrix2(const T& x, const T& y, const T& z, const T& w) {
    m_data = {x, y, z, w};
}
template Matrix2<int>::Matrix2(const int& x, const int& y, const int& z, const int& w);
template Matrix2<float>::Matrix2(const float& x, const float& y, const float& z, const float& w);
template Matrix2<double>::Matrix2(const double& x, const double& y, const double& z, const double& w);

template <typename T>
T Matrix2<T>::operator[](int index) const {
    return m_data[index];
}
template int Matrix2<int>::operator[](int index) const;
template float Matrix2<float>::operator[](int index) const;
template double Matrix2<double>::operator[](int index) const;

template <typename T>
T Matrix2<T>::get(int i, int j) const {
    return m_data[(i - 1) + 2 * (j - 1)];
}
template int Matrix2<int>::get(int i, int j) const;
template float Matrix2<float>::get(int i, int j) const;
template double Matrix2<double>::get(int i, int j) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& other) const {
    return {m_data[0] + other[0], m_data[1] + other[1], m_data[2] + other[2], m_data[3] + other[3]};
}
template Matrix2<int> Matrix2<int>::operator+(const Matrix2<int>& other) const;
template Matrix2<float> Matrix2<float>::operator+(const Matrix2<float>& other) const;
template Matrix2<double> Matrix2<double>::operator+(const Matrix2<double>& other) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& other) const {
    return {m_data[0] - other[0], m_data[1] - other[1], m_data[2] - other[2], m_data[3] - other[3]};
}
template Matrix2<int> Matrix2<int>::operator-(const Matrix2<int>& other) const;
template Matrix2<float> Matrix2<float>::operator-(const Matrix2<float>& other) const;
template Matrix2<double> Matrix2<double>::operator-(const Matrix2<double>& other) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator*(const T& other) const {
    return {m_data[0] * other, m_data[1] * other, m_data[2] * other, m_data[3] * other};
}
template Matrix2<int> Matrix2<int>::operator*(const int& other) const;
template Matrix2<float> Matrix2<float>::operator*(const float& other) const;
template Matrix2<double> Matrix2<double>::operator*(const double& other) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator/(const T& other) const {
    return {m_data[0] / other, m_data[1] / other, m_data[2] / other, m_data[3] / other};
}
template Matrix2<int> Matrix2<int>::operator/(const int& other) const;
template Matrix2<float> Matrix2<float>::operator/(const float& other) const;
template Matrix2<double> Matrix2<double>::operator/(const double& other) const;

template <typename T>
Vector2<T> Matrix2<T>::operator*(const Vector2<T>& other) const {
    return {
        m_data[0] * other.x + m_data[1] * other.y,
        m_data[2] * other.x + m_data[3] * other.y,
    };
}
template Vector2<int> Matrix2<int>::operator*(const Vector2<int>& other) const;
template Vector2<float> Matrix2<float>::operator*(const Vector2<float>& other) const;
template Vector2<double> Matrix2<double>::operator*(const Vector2<double>& other) const;

template <typename T>
Vector2<T> Matrix2<T>::operator/(const Vector2<T>& other) const {
    return invert() * other;
}
template Vector2<int> Matrix2<int>::operator/(const Vector2<int>& other) const;
template Vector2<float> Matrix2<float>::operator/(const Vector2<float>& other) const;
template Vector2<double> Matrix2<double>::operator/(const Vector2<double>& other) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& other) const {
    return {
        m_data[0] * other[0] + m_data[1] * other[2],
        m_data[0] * other[1] + m_data[1] * other[3],
        m_data[2] * other[0] + m_data[3] * other[2],
        m_data[2] * other[1] + m_data[3] * other[3],
    };
}
template Matrix2<int> Matrix2<int>::operator*(const Matrix2<int>& other) const;
template Matrix2<float> Matrix2<float>::operator*(const Matrix2<float>& other) const;
template Matrix2<double> Matrix2<double>::operator*(const Matrix2<double>& other) const;

template <typename T>
Matrix2<T> Matrix2<T>::operator/(const Matrix2<T>& other) const {
    return invert() * other;
}
template Matrix2<int> Matrix2<int>::operator/(const Matrix2<int>& other) const;
template Matrix2<float> Matrix2<float>::operator/(const Matrix2<float>& other) const;
template Matrix2<double> Matrix2<double>::operator/(const Matrix2<double>& other) const;

template <typename T>
T Matrix2<T>::determinant() const {
    return m_data[0] * m_data[3] - m_data[1] * m_data[2];
}
template int Matrix2<int>::determinant() const;
template float Matrix2<float>::determinant() const;
template double Matrix2<double>::determinant() const;

template <typename T>
Matrix2<T> Matrix2<T>::transpose() const {
    return {m_data[0], m_data[2], m_data[1], m_data[3]};
}
template Matrix2<int> Matrix2<int>::transpose() const;
template Matrix2<float> Matrix2<float>::transpose() const;
template Matrix2<double> Matrix2<double>::transpose() const;

template <typename T>
Matrix2<T> Matrix2<T>::invert() const {
    T det = determinant();

    if (det == 0) LOG_ERROR("The matrix " + com::to_string(Matrix2<T>(m_data[0], m_data[1], m_data[2], m_data[3])) + " has no inverse")

    T factor = T(1) / det;

    return Matrix2<T>(m_data[3], -m_data[1], -m_data[2], m_data[0]) * factor;
}
template Matrix2<int> Matrix2<int>::invert() const;
template Matrix2<float> Matrix2<float>::invert() const;
template Matrix2<double> Matrix2<double>::invert() const;

}  // namespace gmt

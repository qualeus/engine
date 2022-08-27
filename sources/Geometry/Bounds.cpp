#include "../../include/Geometry/Bounds.hpp"

namespace gmt {

/* Bounds Operators: [Ax1 Ay1 Ax2 Ay2]+[Bx1 By1 Bx2 By2] = [Ax1+Bx1 Ay1+By1 Ax2+Bx2 Ay2+By2] */
template <typename T>
Bounds<T> Bounds<T>::operator+(const Bounds<T>& other) const {
    return Bounds<T>(x1 + other.x1, y1 + other.y1, x2 + other.x2, y2 + other.y2);
}
template Bounds<int> Bounds<int>::operator+(const Bounds<int>& other) const;
template Bounds<float> Bounds<float>::operator+(const Bounds<float>& other) const;
template Bounds<double> Bounds<double>::operator+(const Bounds<double>& other) const;

/* Bounds Operators: [Ax1 Ay1 Ax2 Ay2]-[Bx1 By1 Bx2 By2] = [Ax1-Bx1 Ay1-By1 Ax2-Bx2 Ay2-By2] */
template <typename T>
Bounds<T> Bounds<T>::operator-(const Bounds<T>& other) const {
    return Bounds<T>(x1 - other.x1, y1 - other.y1, x2 - other.x2, y2 - other.y2);
}
template Bounds<int> Bounds<int>::operator-(const Bounds<int>& other) const;
template Bounds<float> Bounds<float>::operator-(const Bounds<float>& other) const;
template Bounds<double> Bounds<double>::operator-(const Bounds<double>& other) const;

/* Scalar Operators: [Ax1 Ay1 Ax2 Ay2]*X = [Ax1*X Ay1*X Ax2*X Ay2*X] */
template <typename T>
Bounds<T> Bounds<T>::operator*(const T& other) const {
    return Bounds<T>(x1 * other, y1 * other, x2 * other, y2 * other);
}
template Bounds<int> Bounds<int>::operator*(const int& other) const;
template Bounds<float> Bounds<float>::operator*(const float& other) const;
template Bounds<double> Bounds<double>::operator*(const double& other) const;

/* Scalar Operators: [Ax1 Ay1 Ax2 Ay2]/X = [Ax1/X Ay1/X Ax2/X Ay2/X] */
template <typename T>
Bounds<T> Bounds<T>::operator/(const T& other) const {
    return Bounds<T>(x1 / other, y1 / other, x2 / other, y2 / other);
}
template Bounds<int> Bounds<int>::operator/(const int& other) const;
template Bounds<float> Bounds<float>::operator/(const float& other) const;
template Bounds<double> Bounds<double>::operator/(const double& other) const;

/* Comparison Operators: [Ax1 Ay1 Ax2 Ay2] == [Bx1 By1 Bx2 By2] */
template <typename T>
bool Bounds<T>::operator==(const Bounds<T>& other) const {
    if (x1 != other.x1) { return false; }
    if (y1 != other.y1) { return false; }
    if (x2 != other.x2) { return false; }
    if (y2 != other.y2) { return false; }
    return true;
}
template bool Bounds<int>::operator==(const Bounds<int>& other) const;
template bool Bounds<float>::operator==(const Bounds<float>& other) const;
template bool Bounds<double>::operator==(const Bounds<double>& other) const;

/* Comparison Operators: [Ax1 Ay1 Ax2 Ay2] == [Bx1 By1 Bx2 By2] */
template <typename T>
bool Bounds<T>::operator!=(const Bounds<T>& other) const {
    return !operator==(other);
}
template bool Bounds<int>::operator!=(const Bounds<int>& other) const;
template bool Bounds<float>::operator!=(const Bounds<float>& other) const;
template bool Bounds<double>::operator!=(const Bounds<double>& other) const;

/* Default Constructor */
template <typename T>
Bounds<T>::Bounds() {
    x1 = T();
    y1 = T();
    x2 = T();
    y2 = T();
}
template Bounds<int>::Bounds();
template Bounds<float>::Bounds();
template Bounds<double>::Bounds();

/* Default Destructor */
template <typename T>
Bounds<T>::~Bounds() { }
template Bounds<int>::~Bounds();
template Bounds<float>::~Bounds();
template Bounds<double>::~Bounds();

/* Builder Constructor */
template <typename T>
Bounds<T>::Bounds(const T& _x1, const T& _y1, const T& _x2, const T& _y2) {
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
}
template Bounds<int>::Bounds(const int& x1, const int& y1, const int& x2, const int& y2);
template Bounds<float>::Bounds(const float& x1, const float& y1, const float& x2, const float& y2);
template Bounds<double>::Bounds(const double& x1, const double& y1, const double& x2, const double& y2);

/* Return the Size of the rectangle */
template <typename T>
Vector2<T> Bounds<T>::size() const {
    return Vector2<T>(x2 - x1, y2 - y1);
}
template Vector2<int> Bounds<int>::size() const;
template Vector2<float> Bounds<float>::size() const;
template Vector2<double> Bounds<double>::size() const;

/* Reorder in an Clockwise order the points */
template <typename T>
Bounds<T> Bounds<T>::reorder() const {
    std::vector<Vector2<T>> points = {Vector2<T>(x1, y1), Vector2<T>(x2, y2)};
    const auto min_max_x = std::minmax_element(points.begin(), points.end(), [](const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.x < rhs.x; });
    const auto min_max_y = std::minmax_element(points.begin(), points.end(), [](const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.y < rhs.y; });
    return Bounds<T>((*min_max_x.first).x, (*min_max_y.first).y, (*min_max_x.second).x, (*min_max_y.second).y);
}
template Bounds<int> Bounds<int>::reorder() const;
template Bounds<float> Bounds<float>::reorder() const;
template Bounds<double> Bounds<double>::reorder() const;

/* Duplication Method */
template <typename T>
Bounds<T> Bounds<T>::clone() const {
    return Bounds<T>(x1, y1, x2, y2);
}
template Bounds<int> Bounds<int>::clone() const;
template Bounds<float> Bounds<float>::clone() const;
template Bounds<double> Bounds<double>::clone() const;

/* Check if a Point is in this Boundaries */
template <typename T>
bool Bounds<T>::point_in_bounds(const Vector2<T>& v1, const Bounds<T>& b2) {
    if (v1.x < b2.x1) { return false; }
    if (v1.x > b2.x2) { return false; }
    if (v1.y < b2.y1) { return false; }
    if (v1.y > b2.y2) { return false; }
    return true;
}
template bool Bounds<int>::point_in_bounds(const Vector2<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::point_in_bounds(const Vector2<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::point_in_bounds(const Vector2<double>& v1, const Bounds<double>& b2);

/* Check if  a Point is out of this Boundaries */
template <typename T>
bool Bounds<T>::point_out_bounds(const Vector2<T>& v1, const Bounds<T>& b2) {
    return !Bounds<T>::point_in_bounds(v1, b2);
}
template bool Bounds<int>::point_out_bounds(const Vector2<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::point_out_bounds(const Vector2<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::point_out_bounds(const Vector2<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is in this Boundaries */
template <typename T>
bool Bounds<T>::circle_in_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2) {
    if (v1.x - r < b2.x1) { return false; }
    if (v1.x + r > b2.x2) { return false; }
    if (v1.y - r < b2.y1) { return false; }
    if (v1.x + r > b2.y2) { return false; }
    return true;
}
template bool Bounds<int>::circle_in_bounds(const int& r, const Vector2<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::circle_in_bounds(const float& r, const Vector2<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::circle_in_bounds(const double& r, const Vector2<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is out of this Boundaries */
template <typename T>
bool Bounds<T>::circle_out_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2) {
    return !Bounds<T>::circle_in_bounds(r, v1, b2);
}
template bool Bounds<int>::circle_out_bounds(const int& r, const Vector2<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::circle_out_bounds(const float& r, const Vector2<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::circle_out_bounds(const double& r, const Vector2<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is out of this Boundaries */
template <typename T>
bool Bounds<T>::circle_intersect_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2) {
    return Bounds<T>::bounds_intersect_bounds(Bounds<T>(v1.x - r, v1.y - r, v1.x + r, v1.y + r), b2);
}
template bool Bounds<int>::circle_intersect_bounds(const int& r, const Vector2<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::circle_intersect_bounds(const float& r, const Vector2<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::circle_intersect_bounds(const double& r, const Vector2<double>& v1, const Bounds<double>& b2);

/* Check if a Vector2 is in this Boundaries */
template <typename T>
bool Bounds<T>::segment_in_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2) {
    if (Bounds<T>::point_out_bounds(v1, b2)) { return false; }
    if (Bounds<T>::point_out_bounds(v2, b2)) { return false; }
    return true;
}
template bool Bounds<int>::segment_in_bounds(const Vector2<int>& v1, const Vector2<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::segment_in_bounds(const Vector2<float>& v1, const Vector2<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::segment_in_bounds(const Vector2<double>& v1, const Vector2<double>& v2, const Bounds<double>& b2);

/* Check if a Vector2 is out of this Boundaries */
template <typename T>
bool Bounds<T>::segment_out_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2) {
    return !Bounds<T>::segment_in_bounds(v1, v2, b2);
}

template bool Bounds<int>::segment_out_bounds(const Vector2<int>& v1, const Vector2<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::segment_out_bounds(const Vector2<float>& v1, const Vector2<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::segment_out_bounds(const Vector2<double>& v1, const Vector2<double>& v2, const Bounds<double>& b2);

/* Check if a Vector2 is in / intersect with this Boundaries */
template <typename T>
bool Bounds<T>::segment_intersect_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2) {
    if (Vector2<T>::segments_intersect(v1, v2, Vector2<T>(b2.x1, b2.y1), Vector2<T>(b2.x2, b2.y1))) { return true; }
    if (Vector2<T>::segments_intersect(v1, v2, Vector2<T>(b2.x2, b2.y1), Vector2<T>(b2.x2, b2.y2))) { return true; }
    if (Vector2<T>::segments_intersect(v1, v2, Vector2<T>(b2.x2, b2.y2), Vector2<T>(b2.x1, b2.y2))) { return true; }
    if (Vector2<T>::segments_intersect(v1, v2, Vector2<T>(b2.x1, b2.y2), Vector2<T>(b2.x1, b2.y1))) { return true; }
    if (Bounds<T>::segment_in_bounds(v1, v2, b2)) { return true; }
    return false;
}
template bool Bounds<int>::segment_intersect_bounds(const Vector2<int>& v1, const Vector2<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::segment_intersect_bounds(const Vector2<float>& v1, const Vector2<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::segment_intersect_bounds(const Vector2<double>& v1, const Vector2<double>& v2, const Bounds<double>& b2);

/* Check if another Bound is in this Boundaries */
template <typename T>
bool Bounds<T>::bounds_in_bounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    if (Bounds<T>::point_out_bounds(Vector2<T>(b1.x1, b1.y1), b2)) { return false; }
    if (Bounds<T>::point_out_bounds(Vector2<T>(b1.x1, b1.y2), b2)) { return false; }
    if (Bounds<T>::point_out_bounds(Vector2<T>(b1.x2, b1.y1), b2)) { return false; }
    if (Bounds<T>::point_out_bounds(Vector2<T>(b1.x2, b1.y2), b2)) { return false; }
    return true;
}
template bool Bounds<int>::bounds_in_bounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::bounds_in_bounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::bounds_in_bounds(const Bounds<double>& b1, const Bounds<double>& b2);

/* Check if another Bound is out of this Boundaries */
template <typename T>
bool Bounds<T>::bounds_out_bounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    return !Bounds<T>::bounds_in_bounds(b1, b2);
}
template bool Bounds<int>::bounds_out_bounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::bounds_out_bounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::bounds_out_bounds(const Bounds<double>& b1, const Bounds<double>& b2);

/* Check if another Bound is in /intersect with this Boundaries */
template <typename T>
bool Bounds<T>::bounds_intersect_bounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    if (Bounds<T>::segment_intersect_bounds(Vector2<T>(b1.x1, b1.y1), Vector2<T>(b1.x2, b1.y1), b2)) { return true; }
    if (Bounds<T>::segment_intersect_bounds(Vector2<T>(b1.x2, b1.y1), Vector2<T>(b1.x2, b1.y2), b2)) { return true; }
    if (Bounds<T>::segment_intersect_bounds(Vector2<T>(b1.x2, b1.y2), Vector2<T>(b1.x1, b1.y2), b2)) { return true; }
    if (Bounds<T>::segment_intersect_bounds(Vector2<T>(b1.x1, b1.y2), Vector2<T>(b1.x1, b1.y1), b2)) { return true; }
    if (Bounds<T>::bounds_in_bounds(b1, b2)) { return true; }
    return false;
}
template bool Bounds<int>::bounds_intersect_bounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::bounds_intersect_bounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::bounds_intersect_bounds(const Bounds<double>& b1, const Bounds<double>& b2);

}  // namespace gmt
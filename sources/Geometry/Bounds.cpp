#include "../../include/Geometry/Bounds.hpp"

namespace gmt {

/* Bounds Operators: [Ax1 Ay1 Ax2 Ay2]+[Bx1 By1 Bx2 By2] = [Ax1+Bx1 Ay1+By1 Ax2+Bx2 Ay2+By2] */
template <typename T>
Bounds<T> Bounds<T>::operator+(const Bounds<T>& other) const {
    return Bounds<T>(this->x1 + other.x1, this->y1 + other.y1, this->x2 + other.x2, this->y2 + other.y2);
}
template Bounds<int> Bounds<int>::operator+(const Bounds<int>& other) const;
template Bounds<float> Bounds<float>::operator+(const Bounds<float>& other) const;
template Bounds<double> Bounds<double>::operator+(const Bounds<double>& other) const;

/* Bounds Operators: [Ax1 Ay1 Ax2 Ay2]-[Bx1 By1 Bx2 By2] = [Ax1-Bx1 Ay1-By1 Ax2-Bx2 Ay2-By2] */
template <typename T>
Bounds<T> Bounds<T>::operator-(const Bounds<T>& other) const {
    return Bounds<T>(this->x1 - other.x1, this->y1 - other.y1, this->x2 - other.x2, this->y2 - other.y2);
}
template Bounds<int> Bounds<int>::operator-(const Bounds<int>& other) const;
template Bounds<float> Bounds<float>::operator-(const Bounds<float>& other) const;
template Bounds<double> Bounds<double>::operator-(const Bounds<double>& other) const;

/* Scalar Operators: [Ax1 Ay1 Ax2 Ay2]*X = [Ax1*X Ay1*X Ax2*X Ay2*X] */
template <typename T>
Bounds<T> Bounds<T>::operator*(const T& other) const {
    return Bounds<T>(this->x1 * other, this->y1 * other, this->x2 * other, this->y2 * other);
}
template Bounds<int> Bounds<int>::operator*(const int& other) const;
template Bounds<float> Bounds<float>::operator*(const float& other) const;
template Bounds<double> Bounds<double>::operator*(const double& other) const;

/* Scalar Operators: [Ax1 Ay1 Ax2 Ay2]/X = [Ax1/X Ay1/X Ax2/X Ay2/X] */
template <typename T>
Bounds<T> Bounds<T>::operator/(const T& other) const {
    return Bounds<T>(this->x1 / other, this->y1 / other, this->x2 / other, this->y2 / other);
}
template Bounds<int> Bounds<int>::operator/(const int& other) const;
template Bounds<float> Bounds<float>::operator/(const float& other) const;
template Bounds<double> Bounds<double>::operator/(const double& other) const;

/* Comparison Operators: [Ax1 Ay1 Ax2 Ay2] == [Bx1 By1 Bx2 By2] */
template <typename T>
bool Bounds<T>::operator==(const Bounds<T>& other) const {
    if (this->x1 != other.x1) { return false; }
    if (this->y1 != other.y1) { return false; }
    if (this->x2 != other.x2) { return false; }
    if (this->y2 != other.y2) { return false; }
    return true;
}
template bool Bounds<int>::operator==(const Bounds<int>& other) const;
template bool Bounds<float>::operator==(const Bounds<float>& other) const;
template bool Bounds<double>::operator==(const Bounds<double>& other) const;

/* Comparison Operators: [Ax1 Ay1 Ax2 Ay2] == [Bx1 By1 Bx2 By2] */
template <typename T>
bool Bounds<T>::operator!=(const Bounds<T>& other) const {
    return !this->operator==(other);
}
template bool Bounds<int>::operator!=(const Bounds<int>& other) const;
template bool Bounds<float>::operator!=(const Bounds<float>& other) const;
template bool Bounds<double>::operator!=(const Bounds<double>& other) const;

/* Default Constructor */
template <typename T>
Bounds<T>::Bounds() {
    this->x1 = T();
    this->y1 = T();
    this->x2 = T();
    this->y2 = T();
}
template Bounds<int>::Bounds();
template Bounds<float>::Bounds();
template Bounds<double>::Bounds();

/* Default Destructor */
template <typename T>
Bounds<T>::~Bounds() {}
template Bounds<int>::~Bounds();
template Bounds<float>::~Bounds();
template Bounds<double>::~Bounds();

/* Builder Constructor */
template <typename T>
Bounds<T>::Bounds(const T& x1, const T& y1, const T& x2, const T& y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}
template Bounds<int>::Bounds(const int& x1, const int& y1, const int& x2, const int& y2);
template Bounds<float>::Bounds(const float& x1, const float& y1, const float& x2, const float& y2);
template Bounds<double>::Bounds(const double& x1, const double& y1, const double& x2, const double& y2);

/* Return the Size of the rectangle */
template <typename T>
Vector<T> Bounds<T>::Size() const {
    return Vector<T>(this->x2 - this->x1, this->y2 - this->y1);
}
template Vector<int> Bounds<int>::Size() const;
template Vector<float> Bounds<float>::Size() const;
template Vector<double> Bounds<double>::Size() const;

/* Reorder in an Clockwise order the points */
template <typename T>
Bounds<T> Bounds<T>::Reorder() const {
    std::vector<Vector<T>> points = {Vector<T>(this->x1, this->y1), Vector<T>(this->x2, this->y2)};
    const auto min_max_x = std::minmax_element(points.begin(), points.end(), [](const Vector<T>& lhs, const Vector<T>& rhs) { return lhs.x < rhs.x; });
    const auto min_max_y = std::minmax_element(points.begin(), points.end(), [](const Vector<T>& lhs, const Vector<T>& rhs) { return lhs.y < rhs.y; });
    return Bounds<T>((*min_max_x.first).x, (*min_max_y.first).y, (*min_max_x.second).x, (*min_max_y.second).y);
}
template Bounds<int> Bounds<int>::Reorder() const;
template Bounds<float> Bounds<float>::Reorder() const;
template Bounds<double> Bounds<double>::Reorder() const;

/* Duplication Method */
template <typename T>
Bounds<T> Bounds<T>::Clone() const {
    return Bounds<T>(this->x1, this->y1, this->x2, this->y2);
}
template Bounds<int> Bounds<int>::Clone() const;
template Bounds<float> Bounds<float>::Clone() const;
template Bounds<double> Bounds<double>::Clone() const;

/* Check if a Point is in this Boundaries */
template <typename T>
bool Bounds<T>::PointInBounds(const Vector<T>& v1, const Bounds<T>& b2) {
    if (v1.x < b2.x1) { return false; }
    if (v1.x > b2.x2) { return false; }
    if (v1.y < b2.y1) { return false; }
    if (v1.y > b2.y2) { return false; }
    return true;
}
template bool Bounds<int>::PointInBounds(const Vector<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::PointInBounds(const Vector<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::PointInBounds(const Vector<double>& v1, const Bounds<double>& b2);

/* Check if  a Point is out of this Boundaries */
template <typename T>
bool Bounds<T>::PointOutBounds(const Vector<T>& v1, const Bounds<T>& b2) {
    return !Bounds<T>::PointInBounds(v1, b2);
}
template bool Bounds<int>::PointOutBounds(const Vector<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::PointOutBounds(const Vector<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::PointOutBounds(const Vector<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is in this Boundaries */
template <typename T>
bool Bounds<T>::CircleInBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2) {
    if (v1.x - r < b2.x1) { return false; }
    if (v1.x + r > b2.x2) { return false; }
    if (v1.y - r < b2.y1) { return false; }
    if (v1.x + r > b2.y2) { return false; }
    return true;
}
template bool Bounds<int>::CircleInBounds(const int& r, const Vector<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::CircleInBounds(const float& r, const Vector<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::CircleInBounds(const double& r, const Vector<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is out of this Boundaries */
template <typename T>
bool Bounds<T>::CircleOutBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2) {
    return !Bounds<T>::CircleInBounds(r, v1, b2);
}
template bool Bounds<int>::CircleOutBounds(const int& r, const Vector<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::CircleOutBounds(const float& r, const Vector<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::CircleOutBounds(const double& r, const Vector<double>& v1, const Bounds<double>& b2);

/* Check if a Circle is out of this Boundaries */
template <typename T>
bool Bounds<T>::CircleIntersectBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2) {
    return Bounds<T>::BoundsIntersectBounds(Bounds<T>(v1.x - r, v1.y - r, v1.x + r, v1.y + r), b2);
}
template bool Bounds<int>::CircleIntersectBounds(const int& r, const Vector<int>& v1, const Bounds<int>& b2);
template bool Bounds<float>::CircleIntersectBounds(const float& r, const Vector<float>& v1, const Bounds<float>& b2);
template bool Bounds<double>::CircleIntersectBounds(const double& r, const Vector<double>& v1, const Bounds<double>& b2);

/* Check if a Vector is in this Boundaries */
template <typename T>
bool Bounds<T>::SegmentInBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2) {
    if (Bounds<T>::PointOutBounds(v1, b2)) { return false; }
    if (Bounds<T>::PointOutBounds(v2, b2)) { return false; }
    return true;
}
template bool Bounds<int>::SegmentInBounds(const Vector<int>& v1, const Vector<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::SegmentInBounds(const Vector<float>& v1, const Vector<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::SegmentInBounds(const Vector<double>& v1, const Vector<double>& v2, const Bounds<double>& b2);

/* Check if a Vector is out of this Boundaries */
template <typename T>
bool Bounds<T>::SegmentOutBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2) {
    return !Bounds<T>::SegmentInBounds(v1, v2, b2);
}

template bool Bounds<int>::SegmentOutBounds(const Vector<int>& v1, const Vector<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::SegmentOutBounds(const Vector<float>& v1, const Vector<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::SegmentOutBounds(const Vector<double>& v1, const Vector<double>& v2, const Bounds<double>& b2);

/* Check if a Vector is in / intersect with this Boundaries */
template <typename T>
bool Bounds<T>::SegmentIntersectBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2) {
    if (Vector<T>::SegmentsIntersect(v1, v2, Vector<T>(b2.x1, b2.y1), Vector<T>(b2.x2, b2.y1))) { return true; }
    if (Vector<T>::SegmentsIntersect(v1, v2, Vector<T>(b2.x2, b2.y1), Vector<T>(b2.x2, b2.y2))) { return true; }
    if (Vector<T>::SegmentsIntersect(v1, v2, Vector<T>(b2.x2, b2.y2), Vector<T>(b2.x1, b2.y2))) { return true; }
    if (Vector<T>::SegmentsIntersect(v1, v2, Vector<T>(b2.x1, b2.y2), Vector<T>(b2.x1, b2.y1))) { return true; }
    if (Bounds<T>::SegmentInBounds(v1, v2, b2)) { return true; }
    return false;
}
template bool Bounds<int>::SegmentIntersectBounds(const Vector<int>& v1, const Vector<int>& v2, const Bounds<int>& b2);
template bool Bounds<float>::SegmentIntersectBounds(const Vector<float>& v1, const Vector<float>& v2, const Bounds<float>& b2);
template bool Bounds<double>::SegmentIntersectBounds(const Vector<double>& v1, const Vector<double>& v2, const Bounds<double>& b2);

/* Check if another Bound is in this Boundaries */
template <typename T>
bool Bounds<T>::BoundsInBounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    if (Bounds<T>::PointOutBounds(Vector<T>(b1.x1, b1.y1), b2)) { return false; }
    if (Bounds<T>::PointOutBounds(Vector<T>(b1.x1, b1.y2), b2)) { return false; }
    if (Bounds<T>::PointOutBounds(Vector<T>(b1.x2, b1.y1), b2)) { return false; }
    if (Bounds<T>::PointOutBounds(Vector<T>(b1.x2, b1.y2), b2)) { return false; }
    return true;
}
template bool Bounds<int>::BoundsInBounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::BoundsInBounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::BoundsInBounds(const Bounds<double>& b1, const Bounds<double>& b2);

/* Check if another Bound is out of this Boundaries */
template <typename T>
bool Bounds<T>::BoundsOutBounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    return !Bounds<T>::BoundsInBounds(b1, b2);
}
template bool Bounds<int>::BoundsOutBounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::BoundsOutBounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::BoundsOutBounds(const Bounds<double>& b1, const Bounds<double>& b2);

/* Check if another Bound is in /intersect with this Boundaries */
template <typename T>
bool Bounds<T>::BoundsIntersectBounds(const Bounds<T>& b1, const Bounds<T>& b2) {
    if (Bounds<T>::SegmentIntersectBounds(Vector<T>(b1.x1, b1.y1), Vector<T>(b1.x2, b1.y1), b2)) { return true; }
    if (Bounds<T>::SegmentIntersectBounds(Vector<T>(b1.x2, b1.y1), Vector<T>(b1.x2, b1.y2), b2)) { return true; }
    if (Bounds<T>::SegmentIntersectBounds(Vector<T>(b1.x2, b1.y2), Vector<T>(b1.x1, b1.y2), b2)) { return true; }
    if (Bounds<T>::SegmentIntersectBounds(Vector<T>(b1.x1, b1.y2), Vector<T>(b1.x1, b1.y1), b2)) { return true; }
    if (Bounds<T>::BoundsInBounds(b1, b2)) { return true; }
    return false;
}
template bool Bounds<int>::BoundsIntersectBounds(const Bounds<int>& b1, const Bounds<int>& b2);
template bool Bounds<float>::BoundsIntersectBounds(const Bounds<float>& b1, const Bounds<float>& b2);
template bool Bounds<double>::BoundsIntersectBounds(const Bounds<double>& b1, const Bounds<double>& b2);

}  // namespace gmt
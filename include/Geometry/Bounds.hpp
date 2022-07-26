#ifndef Bounds_HPP
#define Bounds_HPP

#include "../Common/Maths.hpp"
#include "Vector.hpp"

namespace gmt {

template <typename T>
class Bounds {
   public:
    T x1;
    T y1;
    T x2;
    T y2;

    Bounds<T> operator+(const Bounds<T>& other) const;
    Bounds<T> operator-(const Bounds<T>& other) const;
    Bounds<T> operator*(const T& other) const;
    Bounds<T> operator/(const T& other) const;

    bool operator==(const Bounds<T>& other) const;
    bool operator!=(const Bounds<T>& other) const;

    Bounds(const T& x1, const T& y1, const T& x2, const T& y2);
    Bounds();
    ~Bounds();

    Vector<T> Size() const;
    Bounds<T> Reorder() const;
    Bounds<T> Clone() const;

    static bool PointInBounds(const Vector<T>& v1, const Bounds<T>& b2);
    static bool PointOutBounds(const Vector<T>& v1, const Bounds<T>& b2);

    static bool CircleInBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2);
    static bool CircleOutBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2);
    static bool CircleIntersectBounds(const T& r, const Vector<T>& v1, const Bounds<T>& b2);

    static bool SegmentInBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2);
    static bool SegmentOutBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2);
    static bool SegmentIntersectBounds(const Vector<T>& v1, const Vector<T>& v2, const Bounds<T>& b2);

    static bool BoundsInBounds(const Bounds<T>& b1, const Bounds<T>& b2);
    static bool BoundsOutBounds(const Bounds<T>& b1, const Bounds<T>& b2);
    static bool BoundsIntersectBounds(const Bounds<T>& b1, const Bounds<T>& b2);
};
}  // namespace gmt

#endif
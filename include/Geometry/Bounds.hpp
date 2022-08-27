#ifndef Bounds_HPP
#define Bounds_HPP

#include "../Common/Maths.hpp"
#include "Vector2.hpp"

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

    Vector2<T> size() const;
    Bounds<T> reorder() const;
    Bounds<T> clone() const;

    static bool point_in_bounds(const Vector2<T>& v1, const Bounds<T>& b2);
    static bool point_out_bounds(const Vector2<T>& v1, const Bounds<T>& b2);

    static bool circle_in_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2);
    static bool circle_out_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2);
    static bool circle_intersect_bounds(const T& r, const Vector2<T>& v1, const Bounds<T>& b2);

    static bool segment_in_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2);
    static bool segment_out_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2);
    static bool segment_intersect_bounds(const Vector2<T>& v1, const Vector2<T>& v2, const Bounds<T>& b2);

    static bool bounds_in_bounds(const Bounds<T>& b1, const Bounds<T>& b2);
    static bool bounds_out_bounds(const Bounds<T>& b1, const Bounds<T>& b2);
    static bool bounds_intersect_bounds(const Bounds<T>& b1, const Bounds<T>& b2);
};
}  // namespace gmt

#endif
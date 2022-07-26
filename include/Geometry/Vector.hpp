#ifndef Vector_HPP
#define Vector_HPP

#include "../Common/Maths.hpp"

namespace gmt {

template <typename T>
class Vector {
   public:
    T x;
    T y;

    Vector<T> operator+() const;
    Vector<T> operator-() const;
    Vector<T> operator+(const Vector<T>& other) const;
    Vector<T> operator-(const Vector<T>& other) const;
    Vector<T> operator*(const T& other) const;
    Vector<T> operator/(const T& other) const;

    bool operator==(const Vector<T>& other) const;
    bool operator!=(const Vector<T>& other) const;

    Vector(const T& x, const T& y);
    Vector();
    ~Vector();
    T Magnitude() const;
    T MagnitudeSquared() const;

    Vector<T> Clone() const;

    Vector<T> Normalize() const;
    Vector<T> Scale(const T& scale) const;
    Vector<T> Pow(const int& power) const;
    Vector<T> Rotate(const float& angle) const;
    Vector<T> SetAngle(const float& angle) const;

    static T Distance(const Vector<T>& v1, const Vector<T>& v2);
    static T DistanceSquared(const Vector<T>& v1, const Vector<T>& v2);

    static T Dot(const Vector<T>& v1, const Vector<T>& v2);
    static T Cross(const Vector<T>& v1, const Vector<T>& v2);
    static Vector<T> Normal(const Vector<T>& v1);
    static Vector<T> NormalInverted(const Vector<T>& v1);
    static Vector<T> Normal(const Vector<T>& v1, const Vector<T>& v2);
    static Vector<T> NormalInverted(const Vector<T>& v1, const Vector<T>& v2);

    static T Bearing(const Vector<T>& v1, const Vector<T>& v2);
    static T Angle(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3);

    static Vector<T> RotatePoint(const Vector<T>& v1, const Vector<T>& v2, const float& angle);
    static Vector<T> MirroredPoint(const Vector<T>& v1, const Vector<T>& v2);

    static bool PointOnSegment(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3);
    static int LineOrientation(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3);

    static bool SegmentsIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const Vector<T>& v4);
    static bool LinesIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const Vector<T>& v4);
    static std::pair<int, Vector<T>> LineCercleIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const T& size);

    static Vector<T> LineProjection(const Vector<T>& v1, const Vector<T>& v2);
    static Vector<T> SegmentProjection(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3);
};
}  // namespace gmt

#endif
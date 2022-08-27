#ifndef Vector2_HPP
#define Vector2_HPP

#include "../Common/Maths.hpp"

namespace gmt {

template <typename T>
class Vector2 {
   public:
    T x;
    T y;

    Vector2<T> operator+() const;
    Vector2<T> operator-() const;
    Vector2<T> operator+(const Vector2<T>& other) const;
    Vector2<T> operator-(const Vector2<T>& other) const;
    Vector2<T> operator*(const T& other) const;
    Vector2<T> operator/(const T& other) const;

    bool operator==(const Vector2<T>& other) const;
    bool operator!=(const Vector2<T>& other) const;

    Vector2(const T& x, const T& y);
    Vector2();
    ~Vector2();
    T magnitude() const;
    T magnitude_squared() const;

    Vector2<T> clone() const;

    Vector2<T> normalize() const;
    Vector2<T> scale(const T& scale) const;
    Vector2<T> pow(const int& power) const;
    Vector2<T> rotate(const float& angle) const;
    Vector2<T> set_angle(const float& angle) const;

    static T distance(const Vector2<T>& v1, const Vector2<T>& v2);
    static T distance_squared(const Vector2<T>& v1, const Vector2<T>& v2);

    static T dot(const Vector2<T>& v1, const Vector2<T>& v2);
    static T cross(const Vector2<T>& v1, const Vector2<T>& v2);
    static Vector2<T> normal(const Vector2<T>& v1);
    static Vector2<T> normal_inverted(const Vector2<T>& v1);
    static Vector2<T> normal(const Vector2<T>& v1, const Vector2<T>& v2);
    static Vector2<T> normal_inverted(const Vector2<T>& v1, const Vector2<T>& v2);

    static T bearing(const Vector2<T>& v1, const Vector2<T>& v2);
    static T angle(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3);

    static Vector2<T> rotate_point(const Vector2<T>& v1, const Vector2<T>& v2, const float& angle);
    static Vector2<T> mirrored_point(const Vector2<T>& v1, const Vector2<T>& v2);

    static bool point_on_segment(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3);
    static int line_orientation(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3);

    static bool segments_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const Vector2<T>& v4);
    static bool lines_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const Vector2<T>& v4);
    static std::pair<int, Vector2<T>> line_cercle_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const T& size);

    static Vector2<T> line_projection(const Vector2<T>& v1, const Vector2<T>& v2);
    static Vector2<T> segment_projection(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3);
};
}  // namespace gmt

#endif
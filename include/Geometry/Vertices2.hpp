#ifndef Vertices2_HPP
#define Vertices2_HPP

#include "../Common/Maths.hpp"
#include "Bounds.hpp"
#include "Vector2.hpp"

namespace gmt {

template <typename T>
class Vertices2 {
   public:
    std::vector<std::shared_ptr<Vector2<T>>> vertices;

    Vertices2(std::vector<Vector2<T>> vertices);
    Vertices2(std::vector<std::shared_ptr<Vector2<T>>> vertices);
    Vertices2();
    ~Vertices2();

    Vector2<T> centroid() const;
    Vector2<T> average() const;
    std::vector<std::pair<std::shared_ptr<Vector2<T>>, std::shared_ptr<Vector2<T>>>> pairs() const;

    bool intersect() const;
    bool convex() const;
    T area() const;
    std::vector<T> sizes() const;
    Bounds<T> limits() const;

    void reorder();
    void translate(const Vector2<T>& translation);
    void rotate(const T& rotation, const Vector2<T>& centroid);
    void scale(const T& scale, const Vector2<T>& centroid);

    Vertices2<T> hull() const;
    std::vector<Vertices2<T>> triangulate() const;

    static bool orientation_triangle(const Vertices2<T>& vertices);
    static bool point_in_triangle(const Vertices2<T>& vertices, const Vector2<T>& point);
    static bool point_out_triangle(const Vertices2<T>& vertices, const Vector2<T>& point);

    static bool orientation_shape(const Vertices2<T>& vertices);
    static bool point_in_shape(const Vertices2<T>& vertices, const Vector2<T>& point);
    static bool point_out_shape(const Vertices2<T>& vertices, const Vector2<T>& point);

    static std::pair<std::shared_ptr<Vector2<T>>, std::shared_ptr<Vector2<T>>> closest_edge(const Vertices2<T>& vertices, const Vector2<T>& point);
};
}  // namespace gmt
#endif
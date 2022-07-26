#ifndef Vertices_HPP
#define Vertices_HPP

#include "../Common/Maths.hpp"
#include "Bounds.hpp"
#include "Vector.hpp"

namespace gmt {

template <typename T>
class Vertices {
   public:
    std::vector<std::shared_ptr<Vector<T>>> vertices;

    Vertices(std::vector<Vector<T>> vertices);
    Vertices(std::vector<std::shared_ptr<Vector<T>>> vertices);
    Vertices();
    ~Vertices();
    Vector<T> Centroid() const;
    Vector<T> Average() const;
    std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> Pairs() const;

    bool Intersect() const;
    bool Convex() const;
    T Area() const;
    std::vector<T> Sizes() const;
    Bounds<T> Limits() const;

    void Reorder();
    void Translate(const Vector<T>& translation);
    void Rotate(const T& rotation, const Vector<T>& centroid);
    void Scale(const T& scale, const Vector<T>& centroid);

    Vertices<T> Hull() const;
    std::vector<Vertices<T>> Triangulate() const;

    static bool OrientationTriangle(const Vertices<T>& vertices);
    static bool PointInTriangle(const Vertices<T>& vertices, const Vector<T>& point);
    static bool PointOutTriangle(const Vertices<T>& vertices, const Vector<T>& point);

    static bool OrientationShape(const Vertices<T>& vertices);
    static bool PointInShape(const Vertices<T>& vertices, const Vector<T>& point);
    static bool PointOutShape(const Vertices<T>& vertices, const Vector<T>& point);

    static std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> ClosestEdge(const Vertices<T>& vertices, const Vector<T>& point);
};
}  // namespace gmt
#endif
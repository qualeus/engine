#include "../../include/Geometry/Vertices2.hpp"

namespace gmt {

/* Builder Constructor */
template <typename T>
Vertices2<T>::Vertices2(com::vec<Vector2<T>> _vertices) {
    vertices = {};
    for (int i = 0; i < _vertices.size(); i++) { vertices.push_back(_vertices[i]); }
}
template Vertices2<int>::Vertices2(com::vec<Vector2<int>> vertices);
template Vertices2<float>::Vertices2(com::vec<Vector2<float>> vertices);
template Vertices2<double>::Vertices2(com::vec<Vector2<double>> vertices);

/* Default Constructor */
template <typename T>
Vertices2<T>::Vertices2() {
    vertices = {};
}
template Vertices2<int>::Vertices2();
template Vertices2<float>::Vertices2();
template Vertices2<double>::Vertices2();

/* Compute the centroid of the polygon with its edges

    X = SUM[(Xi + Xi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
    Y = SUM[(Yi + Yi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
*/
template <typename T>
Vector2<T> Vertices2<T>::centroid() const {
    Vector2<T> centroid = Vector2<T>();

    T signed_area = T(0);
    T A           = T(0);

    int vertices_size = vertices.size();

    for (int i = 0; i < vertices_size; i++) {
        Vector2<T> pA = vertices[i];
        Vector2<T> pB = vertices[com::modulo(i + 1, vertices_size)];

        A = pA.x * pB.y - pB.x * pA.y;  // Area accumulator

        signed_area = signed_area + A;  // Signed area accumulator

        centroid = centroid + (pA + pB) * A;  // Centroid accumulator
    }

    if (signed_area == 0) { return Vector2<T>(); }

    signed_area = signed_area / T(2);
    centroid    = centroid / static_cast<T>(T(6) * signed_area);

    return centroid;
}
template Vector2<int> Vertices2<int>::centroid() const;
template Vector2<float> Vertices2<float>::centroid() const;
template Vector2<double> Vertices2<double>::centroid() const;

/* Compute the averages of the points */
template <typename T>
Vector2<T> Vertices2<T>::average() const {
    Vector2<T> points_average = Vector2<T>();
    if (vertices.size() == 0) { return points_average; }

    for (int i = 0; i < vertices.size(); i++) { points_average = points_average + vertices[i]; }
    return points_average / static_cast<T>(vertices.size());
}
template Vector2<int> Vertices2<int>::average() const;
template Vector2<float> Vertices2<float>::average() const;
template Vector2<double> Vertices2<double>::average() const;

/* Return the Vectors Pairs in a Clockwise Order */
template <typename T>
com::vec<com::spair<Vector2<T>>> Vertices2<T>::pairs() const {
    com::vec<com::spair<Vector2<T>>> pairs = {};

    int vertices_size = vertices.size();

    for (int i = 0; i < vertices_size; i++) {

        Vector2<T> pA = vertices[i];
        Vector2<T> pB = vertices[com::modulo(i + 1, vertices_size)];

        pairs.push_back({pA, pB});
    }

    return pairs;
}
template com::vec<com::spair<Vector2<int>>> Vertices2<int>::pairs() const;
template com::vec<com::spair<Vector2<float>>> Vertices2<float>::pairs() const;
template com::vec<com::spair<Vector2<double>>> Vertices2<double>::pairs() const;

/* Check if the Polygon is Self Intersecting */
template <typename T>
bool Vertices2<T>::intersect() const {
    com::vec<com::spair<Vector2<T>>> sides = pairs();

    /* triangles are always convex */
    if (sides.size() <= 3) { return false; }

    /* We check for every edges that don't have an edge in common (opposites) if they intersect */
    for (int i = 0; i < sides.size() - 2; i++) {
        for (int j = i + 2; j < sides.size() - (i == 0); j++) {
            com::spair<Vector2<T>> sideA = sides[i];
            com::spair<Vector2<T>> sideB = sides[j];

            if (Vector2<T>::segments_intersect(sideA.first, sideA.second, sideB.first, sideB.second)) { return true; }
        }
    }
    return false;
}
template bool Vertices2<int>::intersect() const;
template bool Vertices2<float>::intersect() const;
template bool Vertices2<double>::intersect() const;

/* Check if the Polygon is Convex */
template <typename T>
bool Vertices2<T>::convex() const {

    /* complex shape when self intersection */
    if (intersect()) { return false; }

    com::vec<com::spair<Vector2<T>>> sides = pairs();

    /* triangles are always convex */
    if (sides.size() <= 3) { return true; }

    /* We test for each point if the angle is oriented in the same direction*/
    Vector2<T> last = sides[sides.size() - 1].first - sides[sides.size() - 1].second;
    Vector2<T> curr = sides[0].second - sides[0].first;

    bool orientation = Vector2<T>::cross(last, curr) > T(0);

    for (int i = 1; i < sides.size(); i++) {

        last = sides[i - 1].first - sides[i - 1].second;
        curr = sides[i].second - sides[i].first;

        bool cross_orientation = Vector2<T>::cross(last, curr) > T(0);

        if (orientation != cross_orientation) { return false; }
    }

    return true;
}
template bool Vertices2<int>::convex() const;
template bool Vertices2<float>::convex() const;
template bool Vertices2<double>::convex() const;

/* Compute the area of the polygon with its edges

    X = SUM[(Xi * Yi+1 - Xi+1 * Yi)] / 2
    Y = SUM[(Xi * Yi+1 - Xi+1 * Yi)] / 2
*/
template <typename T>
T Vertices2<T>::area() const {
    T signed_area = T(0);
    T A           = T(0);

    int vertices_size = vertices.size();

    for (int i = 0; i < vertices_size; i++) {

        Vector2<T> pA = vertices[i];
        Vector2<T> pB = vertices[com::modulo(i + 1, vertices_size)];

        A           = pA.x * pB.y - pB.x * pA.y;
        signed_area = signed_area + A;
    }

    return signed_area / T(2);
}
template int Vertices2<int>::area() const;
template float Vertices2<float>::area() const;
template double Vertices2<double>::area() const;

/* Return the array for the sizes of the sides */
template <typename T>
com::vec<T> Vertices2<T>::sizes() const {
    com::vec<T> sizes = {};
    int vertices_size = vertices.size();

    for (int i = 0; i < vertices_size; i++) {

        Vector2<T> pA = vertices[i];
        Vector2<T> pB = vertices[com::modulo(i + 1, vertices_size)];

        sizes.push_back(Vector2<T>::distance(pA, pB));
    }

    return sizes;
}
template com::vec<int> Vertices2<int>::sizes() const;
template com::vec<float> Vertices2<float>::sizes() const;
template com::vec<double> Vertices2<double>::sizes() const;

/* Return the bounds of the polygon */
template <typename T>
Bounds<T> Vertices2<T>::limits() const {

    const auto min_max_x = std::minmax_element(vertices.begin(), vertices.end(), [](const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.x < rhs.x; });
    const auto min_max_y = std::minmax_element(vertices.begin(), vertices.end(), [](const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.y < rhs.y; });

    Vector2<T> min_x_ptr = *min_max_x.first;
    Vector2<T> max_x_ptr = *min_max_x.second;
    Vector2<T> min_y_ptr = *min_max_y.first;
    Vector2<T> max_y_ptr = *min_max_y.second;

    T min_x = min_x_ptr.x;
    T max_x = max_x_ptr.x;
    T min_y = min_y_ptr.y;
    T max_y = max_y_ptr.y;

    return gmt::Bounds<T>(min_x, min_y, max_x, max_y);
}
template Bounds<int> Vertices2<int>::limits() const;
template Bounds<float> Vertices2<float>::limits() const;
template Bounds<double> Vertices2<double>::limits() const;

/* Reorder if not Counter Clockwise */
template <typename T>
void Vertices2<T>::reorder() {
    if (!Vertices2<T>::orientation_shape(vertices)) { std::reverse(vertices.begin(), vertices.end()); }
}
template void Vertices2<int>::reorder();
template void Vertices2<float>::reorder();
template void Vertices2<double>::reorder();

/* Rotate the points of the Poilygon from the Centroid */
template <typename T>
void Vertices2<T>::rotate(const T& rotation, const Vector2<T>& centroid) {
    com::vec<com::sptr<Vector2<T>>> temp = {};

    for (int i = 0; i < vertices.size(); i++) {

        Vector2<T> diff = vertices[i] - centroid;
        vertices[i]     = centroid + diff.rotate(rotation);
    }
}
template void Vertices2<int>::rotate(const int& rotation, const Vector2<int>& centroid);
template void Vertices2<float>::rotate(const float& rotation, const Vector2<float>& centroid);
template void Vertices2<double>::rotate(const double& rotation, const Vector2<double>& centroid);

/* Translate the points of the Polygon with a translation vector */
template <typename T>
void Vertices2<T>::translate(const Vector2<T>& translation) {

    for (int i = 0; i < vertices.size(); i++) { vertices[i] = vertices[i] + translation; }
}
template void Vertices2<int>::translate(const Vector2<int>& rotation);
template void Vertices2<float>::translate(const Vector2<float>& rotation);
template void Vertices2<double>::translate(const Vector2<double>& rotation);

/* Scale the size of the polygon from the Centroid */
template <typename T>
void Vertices2<T>::scale(const T& scale, const Vector2<T>& centroid) {

    for (int i = 0; i < vertices.size(); i++) {
        Vector2<T> diff = vertices[i] - centroid;
        vertices[i]     = centroid + diff * scale;
    }
}
template void Vertices2<int>::scale(const int& scale, const Vector2<int>& centroid);
template void Vertices2<float>::scale(const float& scale, const Vector2<float>& centroid);
template void Vertices2<double>::scale(const double& scale, const Vector2<double>& centroid);

/* Return True if Counter Clockwise and False if Clockwise / not a triangle */
template <typename T>
bool Vertices2<T>::orientation_triangle(const Vertices2<T>& vertices) {

    if (vertices.vertices.size() < 3) { return false; }

    return (Vector2<T>::line_orientation(vertices.vertices[0], vertices.vertices[1], vertices.vertices[2]) == 1);
}
template bool Vertices2<int>::orientation_triangle(const Vertices2<int>& vertices);
template bool Vertices2<float>::orientation_triangle(const Vertices2<float>& vertices);
template bool Vertices2<double>::orientation_triangle(const Vertices2<double>& vertices);

/* Compute the Barycenytric coordinates of the triangle */
template <typename T>
bool Vertices2<T>::point_in_triangle(const Vertices2<T>& vertices, const Vector2<T>& point) {

    if (vertices.vertices.size() < 3) { return false; }

    bool A = Vector2<T>::line_orientation(point, vertices.vertices[0], vertices.vertices[1]) == 1;
    bool B = Vector2<T>::line_orientation(point, vertices.vertices[1], vertices.vertices[2]) == 1;
    bool C = Vector2<T>::line_orientation(point, vertices.vertices[2], vertices.vertices[0]) == 1;

    return A && B && C;
}
template bool Vertices2<int>::point_in_triangle(const Vertices2<int>& vertices, const Vector2<int>& point);
template bool Vertices2<float>::point_in_triangle(const Vertices2<float>& vertices, const Vector2<float>& point);
template bool Vertices2<double>::point_in_triangle(const Vertices2<double>& vertices, const Vector2<double>& point);

/* Compute the Barycenytric coordinates of the triangle */
template <typename T>
bool Vertices2<T>::point_out_triangle(const Vertices2<T>& vertices, const Vector2<T>& point) {
    return !Vertices2<T>::point_in_triangle(vertices, point);
}
template bool Vertices2<int>::point_out_triangle(const Vertices2<int>& vertices, const Vector2<int>& point);
template bool Vertices2<float>::point_out_triangle(const Vertices2<float>& vertices, const Vector2<float>& point);
template bool Vertices2<double>::point_out_triangle(const Vertices2<double>& vertices, const Vector2<double>& point);

/* Convex Hull - Jarvis algorithm */
template <typename T>
Vertices2<T> Vertices2<T>::hull() const {
    Vertices2<T> hull = Vertices2<T>();

    int l = 0;  // leftmost

    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].x < vertices[l].x) { l = i; }
    }

    int p = l;
    int q = 0;

    while (true) {
        hull.vertices.push_back(vertices[p]);

        q = com::modulo(p + 1, vertices.size());
        for (int i = 0; i < vertices.size(); i++) {
            if (Vector2<T>::line_orientation(vertices[p], vertices[i], vertices[q]) == 2) { q = i; }
        }

        p = q;
        if (p == l) { break; }
    }

    hull.reorder();
    return gmt::Vertices2<T>(hull);
}
template Vertices2<int> Vertices2<int>::hull() const;
template Vertices2<float> Vertices2<float>::hull() const;
template Vertices2<double> Vertices2<double>::hull() const;

/* Ear Clipping */
template <typename T>
com::vec<Vertices2<T>> Vertices2<T>::triangulate() const {

    com::vec<Vertices2<T>> triangles = {};
    Vertices2<T> cvertices           = Vertices2<T>();

    for (int i = 0; i < vertices.size(); i++) { cvertices.vertices.push_back(vertices[i]); }

    if (vertices.size() < 4) {
        triangles.push_back(cvertices);
        return triangles;
    }

    // Iterate through vertices
    while (cvertices.vertices.size() >= 3) {
        const int psize = cvertices.vertices.size();
        bool removed    = false;

        for (int i = 0; i < psize; i++) {
            Vector2<T> pA = cvertices.vertices[i];
            Vector2<T> pB = cvertices.vertices[com::modulo(i + 1, psize)];
            Vector2<T> pC = cvertices.vertices[com::modulo(i + 2, psize)];

            Vertices2<T> triangle = Vertices2<T>({pC, pB, pA});

            // If the vertex is concave, skip
            const bool convex = Vertices2<T>::orientation_triangle(triangle);
            if (!convex) { continue; }

            bool contains_point = false;
            for (int j = 0; j < psize; j++) {
                if (point_in_triangle(triangle, cvertices.vertices[j])) {
                    contains_point = true;
                    break;
                }
            }
            if (contains_point) { continue; }  // If the triangle formed by the vertex has other vertices in it, skip

            removed = true;
            triangles.push_back(triangle);  // Otherwise, ear found

            cvertices.vertices.erase(std::begin(cvertices.vertices) + com::modulo(i + 1, psize));
            break;
        }
        if (!removed) {
            // Check here if the polygon is self - intersecting => Convert to Convex Hull?
            break;
        }
    }
    return triangles;
}
template com::vec<Vertices2<int>> Vertices2<int>::triangulate() const;
template com::vec<Vertices2<float>> Vertices2<float>::triangulate() const;
template com::vec<Vertices2<double>> Vertices2<double>::triangulate() const;

/* Return True if Counter Clockwise and False if Clockwise  */
template <typename T>
bool Vertices2<T>::orientation_shape(const Vertices2<T>& vertices) {
    T orientation           = T(0);
    const int vertices_size = vertices.vertices.size();

    for (int i = 0; i < vertices_size; i++) {

        Vector2<T> pA = vertices.vertices[i];
        Vector2<T> pB = vertices.vertices[com::modulo(i + 1, vertices_size)];

        orientation += Vector2<T>::cross(pA, pB);
    }

    return (orientation < T(0));
}

template bool Vertices2<int>::orientation_shape(const Vertices2<int>& vertices);
template bool Vertices2<float>::orientation_shape(const Vertices2<float>& vertices);
template bool Vertices2<double>::orientation_shape(const Vertices2<double>& vertices);

/* Ray Casting Method - Return true if the point is contained in the shape */
template <typename T>
bool Vertices2<T>::point_in_shape(const Vertices2<T>& vertices, const Vector2<T>& point) {
    gmt::Bounds<T> bounds = vertices.limits();

    // The ray of the length is the distance to the farthest horizontal point
    // const auto max_x = std::max_element(vertices.vertices.begin(), vertices.vertices.end(), [](const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.x < rhs.x; });
    // T ray_lenght     = std::abs(*max_x.x - point.x);

    T ray_lenght = T(1000000000000);

    Vector2<T> pointB = Vector2<T>(point.x + ray_lenght, point.y);
    int intersections = 0;
    int vertices_size = vertices.vertices.size();

    for (int i = 0; i < vertices_size; i++) {
        Vector2<T> pA = vertices.vertices[i];
        Vector2<T> pB = vertices.vertices[com::modulo(i + 1, vertices_size)];

        if (Vector2<T>::segments_intersect(point, pointB, pA, pB)) { intersections++; }
    }

    if ((intersections & 1) == 1) { return true; }  // Unpair number of intersection
    return false;
}
template bool Vertices2<int>::point_in_shape(const Vertices2<int>& vertices, const Vector2<int>& point);
template bool Vertices2<float>::point_in_shape(const Vertices2<float>& vertices, const Vector2<float>& point);
template bool Vertices2<double>::point_in_shape(const Vertices2<double>& vertices, const Vector2<double>& point);

/* Return true if the point is not in the shape */
template <typename T>
bool Vertices2<T>::point_out_shape(const Vertices2<T>& vertices, const Vector2<T>& point) {
    return !Vertices2<T>::point_in_shape(vertices, point);
}
template bool Vertices2<int>::point_out_shape(const Vertices2<int>& vertices, const Vector2<int>& point);
template bool Vertices2<float>::point_out_shape(const Vertices2<float>& vertices, const Vector2<float>& point);
template bool Vertices2<double>::point_out_shape(const Vertices2<double>& vertices, const Vector2<double>& point);

/* Find the closest edge to the point by finding the closest projected point */
template <typename T>
com::spair<Vector2<T>> Vertices2<T>::closest_edge(const Vertices2<T>& vertices, const Vector2<T>& point) {
    com::vec<com::spair<Vector2<T>>> pairs = vertices.pairs();

    const auto closest = std::min_element(pairs.begin(), pairs.end(), [point](const com::spair<Vector2<T>>& lhs, const com::spair<Vector2<T>>& rhs) {
        Vector2<T> pro_lhs = Vector2<T>::segment_projection(point, lhs.first, lhs.second);
        Vector2<T> pro_rhs = Vector2<T>::segment_projection(point, rhs.first, rhs.second);

        T dot_dist_lhs = Vector2<T>::distance(pro_lhs, point);
        T dot_dist_rhs = Vector2<T>::distance(pro_rhs, point);
        return dot_dist_lhs < dot_dist_rhs;
    });

    com::spair<Vector2<T>> closest_side = (*closest);

    return closest_side;
}
template com::spair<Vector2<int>> Vertices2<int>::closest_edge(const Vertices2<int>& vertices, const Vector2<int>& point);
template com::spair<Vector2<float>> Vertices2<float>::closest_edge(const Vertices2<float>& vertices, const Vector2<float>& point);
template com::spair<Vector2<double>> Vertices2<double>::closest_edge(const Vertices2<double>& vertices, const Vector2<double>& point);

}  // namespace gmt
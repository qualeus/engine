#include "../../include/Geometry/Vertices.hpp"

namespace gmt {

/* Builder Constructor */
template <typename T>
Vertices<T>::Vertices(std::vector<Vector<T>> vertices) {
    this->vertices = {};
    for (int i = 0; i < vertices.size(); i++) { this->vertices.push_back(std::make_shared<Vector<T>>(vertices[i])); }
}
template Vertices<int>::Vertices(std::vector<Vector<int>> vertices);
template Vertices<float>::Vertices(std::vector<Vector<float>> vertices);
template Vertices<double>::Vertices(std::vector<Vector<double>> vertices);

/* Builder Constructor */
template <typename T>
Vertices<T>::Vertices(std::vector<std::shared_ptr<Vector<T>>> vertices) {
    this->vertices = vertices;
}
template Vertices<int>::Vertices(std::vector<std::shared_ptr<Vector<int>>> vertices);
template Vertices<float>::Vertices(std::vector<std::shared_ptr<Vector<float>>> vertices);
template Vertices<double>::Vertices(std::vector<std::shared_ptr<Vector<double>>> vertices);

/* Default Constructor */
template <typename T>
Vertices<T>::Vertices() {
    this->vertices = {};
}
template Vertices<int>::Vertices();
template Vertices<float>::Vertices();
template Vertices<double>::Vertices();

/* Default Destructor */
template <typename T>
Vertices<T>::~Vertices() {}
template Vertices<int>::~Vertices();
template Vertices<float>::~Vertices();
template Vertices<double>::~Vertices();

/* Compute the centroid of the polygon with its edges */
/*
    X = SUM[(Xi + Xi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
    Y = SUM[(Yi + Yi+1) * (Xi * Yi+1 - Xi+1 * Yi)] / 6 / A
*/
template <typename T>
Vector<T> Vertices<T>::Centroid() const {
    Vector<T> centroid = Vector<T>();
    T signed_area = T(0);
    T A = T(0);
    int vertices_size = this->vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        Vector<T> pA = *this->vertices[i];
        Vector<T> pB = *this->vertices[com::modulo(i + 1, vertices_size)];
        A = pA.x * pB.y - pB.x * pA.y;
        signed_area = signed_area + A;
        centroid = centroid + (pA + pB) * A;
    }

    if (signed_area == 0) { return Vector<T>(); }
    signed_area = signed_area / T(2);
    centroid = centroid / static_cast<T>(T(6) * signed_area);
    return centroid;
}
template Vector<int> Vertices<int>::Centroid() const;
template Vector<float> Vertices<float>::Centroid() const;
template Vector<double> Vertices<double>::Centroid() const;

/* Compute the averages of the points */
template <typename T>
Vector<T> Vertices<T>::Average() const {
    Vector<T> points_average = Vector<T>();
    if (this->vertices.size() == 0) { return points_average; }

    for (int i = 0; i < this->vertices.size(); i++) { points_average = points_average + *this->vertices[i]; }
    return points_average / static_cast<T>(this->vertices.size());
}
template Vector<int> Vertices<int>::Average() const;
template Vector<float> Vertices<float>::Average() const;
template Vector<double> Vertices<double>::Average() const;

/* Return the Vectors Pairs in a Clockwise Order */
template <typename T>
std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> Vertices<T>::Pairs() const {
    std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> pairs = {};
    int vertices_size = this->vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        std::shared_ptr<Vector<T>> pA = this->vertices[i];
        std::shared_ptr<Vector<T>> pB = this->vertices[com::modulo(i + 1, vertices_size)];
        pairs.push_back({pA, pB});
    }
    return pairs;
}
template std::vector<std::pair<std::shared_ptr<Vector<int>>, std::shared_ptr<Vector<int>>>> Vertices<int>::Pairs() const;
template std::vector<std::pair<std::shared_ptr<Vector<float>>, std::shared_ptr<Vector<float>>>> Vertices<float>::Pairs() const;
template std::vector<std::pair<std::shared_ptr<Vector<double>>, std::shared_ptr<Vector<double>>>> Vertices<double>::Pairs() const;

/* Check if the Polygon is Self Intersecting */
template <typename T>
bool Vertices<T>::Intersect() const {
    std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> sides = this->Pairs();
    if (sides.size() <= 3) { return false; } /* triangles are always convex */

    /* We check for every edges that don't have an edge in common (opposites) if they intersect */
    for (int i = 0; i < sides.size() - 2; i++) {
        for (int j = i + 2; j < sides.size() - (i == 0); j++) {
            std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> sideA = sides[i];
            std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> sideB = sides[j];
            if (Vector<T>::SegmentsIntersect(*sideA.first, *sideA.second, *sideB.first, *sideB.second)) { return true; }
        }
    }
    return false;
}
template bool Vertices<int>::Intersect() const;
template bool Vertices<float>::Intersect() const;
template bool Vertices<double>::Intersect() const;

/* Check if the Polygon is Convex */
template <typename T>
bool Vertices<T>::Convex() const {
    std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> sides = this->Pairs();
    if (sides.size() <= 3) { return true; } /* triangles are always convex */

    /* We check for every edges that don't have an edge in common (opposites) if they intersect */
    for (int i = 0; i < sides.size() - 2; i++) {
        for (int j = i + 2; j < sides.size() - (i == 0); j++) {
            std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> sideA = sides[i];
            std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> sideB = sides[j];
            if (Vector<T>::SegmentsIntersect(*sideA.first, *sideA.second, *sideB.first, *sideB.second)) { return false; }
        }
    }

    /* We test for each point if the angle is oriented in the same direction*/
    Vector<T> last = *sides[sides.size() - 1].first - *sides[sides.size() - 1].second;
    Vector<T> curr = *sides[0].second - *sides[0].first;

    bool orientation = Vector<T>::Cross(last, curr) > T(0);

    for (int i = 1; i < sides.size(); i++) {
        last = *sides[i - 1].first - *sides[i - 1].second;
        curr = *sides[i].second - *sides[i].first;
        bool corientation = Vector<T>::Cross(last, curr) > T(0);

        if (orientation != corientation) { return false; }
    }
    return true;
}
template bool Vertices<int>::Convex() const;
template bool Vertices<float>::Convex() const;
template bool Vertices<double>::Convex() const;

/* Compute the area of the polygon with its edges */
/*
    X = SUM[(Xi * Yi+1 - Xi+1 * Yi)] / 2
    Y = SUM[(Xi * Yi+1 - Xi+1 * Yi)] / 2
*/
template <typename T>
T Vertices<T>::Area() const {
    T signed_area = T(0);
    T A = T(0);
    int vertices_size = this->vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        Vector<T> pA = *this->vertices[i];
        Vector<T> pB = *this->vertices[com::modulo(i + 1, vertices_size)];
        A = pA.x * pB.y - pB.x * pA.y;
        signed_area = signed_area + A;
    }
    return signed_area / T(2);
}
template int Vertices<int>::Area() const;
template float Vertices<float>::Area() const;
template double Vertices<double>::Area() const;

/* Return the array for the sizes of the sides */
template <typename T>
std::vector<T> Vertices<T>::Sizes() const {
    std::vector<T> sizes = {};
    int vertices_size = this->vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        Vector<T> pA = *this->vertices[i];
        Vector<T> pB = *this->vertices[com::modulo(i + 1, vertices_size)];
        sizes.push_back(Vector<T>::Distance(pA, pB));
    }
    return sizes;
}
template std::vector<int> Vertices<int>::Sizes() const;
template std::vector<float> Vertices<float>::Sizes() const;
template std::vector<double> Vertices<double>::Sizes() const;

/* Return the bounds of the polygon */
template <typename T>
Bounds<T> Vertices<T>::Limits() const {
    const auto min_max_x = std::minmax_element(vertices.begin(), vertices.end(), [](const std::shared_ptr<Vector<T>>& lhs, const std::shared_ptr<Vector<T>>& rhs) { return (*lhs).x < (*rhs).x; });
    const auto min_max_y = std::minmax_element(vertices.begin(), vertices.end(), [](const std::shared_ptr<Vector<T>>& lhs, const std::shared_ptr<Vector<T>>& rhs) { return (*lhs).y < (*rhs).y; });

    std::shared_ptr<Vector<T>> min_x_ptr = *min_max_x.first;
    std::shared_ptr<Vector<T>> max_x_ptr = *min_max_x.second;
    std::shared_ptr<Vector<T>> min_y_ptr = *min_max_y.first;
    std::shared_ptr<Vector<T>> max_y_ptr = *min_max_y.second;

    T min_x = min_x_ptr->x;
    T max_x = max_x_ptr->x;
    T min_y = min_y_ptr->y;
    T max_y = max_y_ptr->y;

    return gmt::Bounds<T>(min_x, min_y, max_x, max_y);
}
template Bounds<int> Vertices<int>::Limits() const;
template Bounds<float> Vertices<float>::Limits() const;
template Bounds<double> Vertices<double>::Limits() const;

/* Reorder if not Counter Clockwise */
template <typename T>
void Vertices<T>::Reorder() {
    if (!Vertices<T>::OrientationShape(this->vertices)) { std::reverse(this->vertices.begin(), this->vertices.end()); }
}
template void Vertices<int>::Reorder();
template void Vertices<float>::Reorder();
template void Vertices<double>::Reorder();

/* Rotate the points of the Poilygon from the Centroid */
template <typename T>
void Vertices<T>::Rotate(const T& rotation, const Vector<T>& centroid) {
    std::vector<std::shared_ptr<Vector<T>>> temp = {};
    for (int i = 0; i < this->vertices.size(); i++) {
        Vector<T> diff = *this->vertices[i] - centroid;
        *this->vertices[i] = centroid + diff.Rotate(rotation);
    }
}
template void Vertices<int>::Rotate(const int& rotation, const Vector<int>& centroid);
template void Vertices<float>::Rotate(const float& rotation, const Vector<float>& centroid);
template void Vertices<double>::Rotate(const double& rotation, const Vector<double>& centroid);

/* Translate the points of the Poilygon with a translation vector */
template <typename T>
void Vertices<T>::Translate(const Vector<T>& translation) {
    for (int i = 0; i < this->vertices.size(); i++) { *this->vertices[i] = *this->vertices[i] + translation; }
}
template void Vertices<int>::Translate(const Vector<int>& rotation);
template void Vertices<float>::Translate(const Vector<float>& rotation);
template void Vertices<double>::Translate(const Vector<double>& rotation);

/* Scale the size of the polygon from the Centroid */
template <typename T>
void Vertices<T>::Scale(const T& scale, const Vector<T>& centroid) {
    for (int i = 0; i < this->vertices.size(); i++) {
        Vector<T> diff = *this->vertices[i] - centroid;
        *this->vertices[i] = centroid + diff * scale;
    }
}
template void Vertices<int>::Scale(const int& scale, const Vector<int>& centroid);
template void Vertices<float>::Scale(const float& scale, const Vector<float>& centroid);
template void Vertices<double>::Scale(const double& scale, const Vector<double>& centroid);

/* Return True if Counter Clockwise and False if Clockwise / not a triangle */
template <typename T>
bool Vertices<T>::OrientationTriangle(const Vertices<T>& vertices) {
    if (vertices.vertices.size() < 3) { return false; }
    return (Vector<T>::LineOrientation(*vertices.vertices[0], *vertices.vertices[1], *vertices.vertices[2]) == 1);
}
template bool Vertices<int>::OrientationTriangle(const Vertices<int>& vertices);
template bool Vertices<float>::OrientationTriangle(const Vertices<float>& vertices);
template bool Vertices<double>::OrientationTriangle(const Vertices<double>& vertices);

/* Compute the Barycenytric coordinates of the triangle */
template <typename T>
bool Vertices<T>::PointInTriangle(const Vertices<T>& vertices, const Vector<T>& point) {
    if (vertices.vertices.size() < 3) { return false; }
    bool A = Vector<T>::LineOrientation(point, *vertices.vertices[0], *vertices.vertices[1]) == 1;
    bool B = Vector<T>::LineOrientation(point, *vertices.vertices[1], *vertices.vertices[2]) == 1;
    bool C = Vector<T>::LineOrientation(point, *vertices.vertices[2], *vertices.vertices[0]) == 1;
    return A && B && C;
}
template bool Vertices<int>::PointInTriangle(const Vertices<int>& vertices, const Vector<int>& point);
template bool Vertices<float>::PointInTriangle(const Vertices<float>& vertices, const Vector<float>& point);
template bool Vertices<double>::PointInTriangle(const Vertices<double>& vertices, const Vector<double>& point);

/* Compute the Barycenytric coordinates of the triangle */
template <typename T>
bool Vertices<T>::PointOutTriangle(const Vertices<T>& vertices, const Vector<T>& point) {
    return !Vertices<T>::PointInTriangle(vertices, point);
}
template bool Vertices<int>::PointOutTriangle(const Vertices<int>& vertices, const Vector<int>& point);
template bool Vertices<float>::PointOutTriangle(const Vertices<float>& vertices, const Vector<float>& point);
template bool Vertices<double>::PointOutTriangle(const Vertices<double>& vertices, const Vector<double>& point);

/* Convex Hull - Jarvis algorithm */
template <typename T>
Vertices<T> Vertices<T>::Hull() const {
    Vertices<T> hull = Vertices<T>();

    int l = 0;  // leftmost
    for (int i = 0; i < vertices.size(); i++) {
        if ((*vertices[i]).x < (*vertices[l]).x) { l = i; }
    }

    int p = l;
    int q = 0;
    while (true) {
        hull.vertices.push_back(vertices[p]);

        q = com::modulo(p + 1, vertices.size());
        for (int i = 0; i < vertices.size(); i++) {
            if (Vector<T>::LineOrientation(*vertices[p], *vertices[i], *vertices[q]) == 2) { q = i; }
        }
        p = q;
        if (p == l) { break; }
    }
    hull.Reorder();
    return gmt::Vertices<T>(hull);
}
template Vertices<int> Vertices<int>::Hull() const;
template Vertices<float> Vertices<float>::Hull() const;
template Vertices<double> Vertices<double>::Hull() const;

/* Ear Clipping */
template <typename T>
std::vector<Vertices<T>> Vertices<T>::Triangulate() const {
    std::vector<Vertices<T>> triangles = {};
    Vertices<T> cvertices = Vertices<T>();
    for (int i = 0; i < this->vertices.size(); i++) { cvertices.vertices.push_back(this->vertices[i]); }
    // cvertices.Reorder();

    if (this->vertices.size() < 4) {
        triangles.push_back(cvertices);
        return triangles;
    }

    // Iterate through vertices
    while (cvertices.vertices.size() >= 3) {
        const int psize = cvertices.vertices.size();
        bool removed = false;
        for (int i = 0; i < psize; i++) {
            std::shared_ptr<Vector<T>> pA = cvertices.vertices[i];
            std::shared_ptr<Vector<T>> pB = cvertices.vertices[com::modulo(i + 1, psize)];
            std::shared_ptr<Vector<T>> pC = cvertices.vertices[com::modulo(i + 2, psize)];

            Vertices<T> triangle = Vertices<T>({pC, pB, pA});

            // If the vertex is concave, skip
            const bool convex = Vertices<T>::OrientationTriangle(triangle);
            if (!convex) { continue; }

            bool containspoint = false;
            for (int j = 0; j < psize; j++) {
                if (PointInTriangle(triangle, *cvertices.vertices[j])) {
                    containspoint = true;
                    break;
                }
            }
            if (containspoint) { continue; }  // If the triangle formed by the vertex has other vertices in it, skip
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
template std::vector<Vertices<int>> Vertices<int>::Triangulate() const;
template std::vector<Vertices<float>> Vertices<float>::Triangulate() const;
template std::vector<Vertices<double>> Vertices<double>::Triangulate() const;

/* Return True if Counter Clockwise and False if Clockwise  */
template <typename T>
bool Vertices<T>::OrientationShape(const Vertices<T>& vertices) {
    T orientation = T(0);
    const int vertices_size = vertices.vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        Vector<T> pA = *vertices.vertices[i];
        Vector<T> pB = *vertices.vertices[com::modulo(i + 1, vertices_size)];
        orientation += Vector<T>::Cross(pA, pB);
    }
    return (orientation < T(0));
}

template bool Vertices<int>::OrientationShape(const Vertices<int>& vertices);
template bool Vertices<float>::OrientationShape(const Vertices<float>& vertices);
template bool Vertices<double>::OrientationShape(const Vertices<double>& vertices);

/* Ray Casting Method - Return true if the point is contained in the shape */
template <typename T>
bool Vertices<T>::PointInShape(const Vertices<T>& vertices, const Vector<T>& point) {
    gmt::Bounds<T> bounds = vertices.Limits();

    // The ray of the length is the distance to the farthest horizontal point
    const auto max_x =
        std::max_element(vertices.vertices.begin(), vertices.vertices.end(), [](const std::shared_ptr<Vector<T>>& lhs, const std::shared_ptr<Vector<T>>& rhs) { return (*lhs).x < (*rhs).x; });
    T ray_lenght = std::abs((*max_x)->x - point.x);

    Vector<T> pointB = Vector<T>(point.x + ray_lenght, point.y);
    int intersections = 0;
    int vertices_size = vertices.vertices.size();
    for (int i = 0; i < vertices_size; i++) {
        Vector<T> pA = *vertices.vertices[i];
        Vector<T> pB = *vertices.vertices[com::modulo(i + 1, vertices_size)];
        if (Vector<T>::SegmentsIntersect(point, pointB, pA, pB)) { intersections++; }
    }

    if ((intersections & 1) == 1) { return true; }  // Unpair number of intersection
    return false;

    return true;
}
template bool Vertices<int>::PointInShape(const Vertices<int>& vertices, const Vector<int>& point);
template bool Vertices<float>::PointInShape(const Vertices<float>& vertices, const Vector<float>& point);
template bool Vertices<double>::PointInShape(const Vertices<double>& vertices, const Vector<double>& point);

/* Return true if the point is not in the shape */
template <typename T>
bool Vertices<T>::PointOutShape(const Vertices<T>& vertices, const Vector<T>& point) {
    return !Vertices<T>::PointInShape(vertices, point);
}
template bool Vertices<int>::PointOutShape(const Vertices<int>& vertices, const Vector<int>& point);
template bool Vertices<float>::PointOutShape(const Vertices<float>& vertices, const Vector<float>& point);
template bool Vertices<double>::PointOutShape(const Vertices<double>& vertices, const Vector<double>& point);

/* Find the closest edge to the point by finding the closest projected point */
template <typename T>
std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> Vertices<T>::ClosestEdge(const Vertices<T>& vertices, const Vector<T>& point) {
    std::vector<std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>> pairs = vertices.Pairs();
    const auto closest =
        std::min_element(pairs.begin(), pairs.end(),
                         [point](const std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>& lhs, const std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>>& rhs) {
                             Vector<T> pro_lhs = Vector<T>::SegmentProjection(point, *lhs.first, *lhs.second);
                             Vector<T> pro_rhs = Vector<T>::SegmentProjection(point, *rhs.first, *rhs.second);

                             T dot_dist_lhs = Vector<T>::Distance(pro_lhs, point);
                             T dot_dist_rhs = Vector<T>::Distance(pro_rhs, point);
                             return dot_dist_lhs < dot_dist_rhs;
                         });
    std::pair<std::shared_ptr<Vector<T>>, std::shared_ptr<Vector<T>>> closest_side = (*closest);
    return closest_side;
}
template std::pair<std::shared_ptr<Vector<int>>, std::shared_ptr<Vector<int>>> Vertices<int>::ClosestEdge(const Vertices<int>& vertices, const Vector<int>& point);
template std::pair<std::shared_ptr<Vector<float>>, std::shared_ptr<Vector<float>>> Vertices<float>::ClosestEdge(const Vertices<float>& vertices, const Vector<float>& point);
template std::pair<std::shared_ptr<Vector<double>>, std::shared_ptr<Vector<double>>> Vertices<double>::ClosestEdge(const Vertices<double>& vertices, const Vector<double>& point);

}  // namespace gmt
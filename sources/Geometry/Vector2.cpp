#include "../../include/Geometry/Vector2.hpp"

namespace gmt {

/* Vectors Operators: +[Ax Ay] = [Ax Ay] */
template <typename T>
Vector2<T> Vector2<T>::operator+() const {
    return Vector2<T>(x, y);
}
template Vector2<int> Vector2<int>::operator+() const;
template Vector2<float> Vector2<float>::operator+() const;
template Vector2<double> Vector2<double>::operator+() const;

/* Vectors Operators: -[Ax Ay] = [-Ax -Ay] */
template <typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}
template Vector2<int> Vector2<int>::operator-() const;
template Vector2<float> Vector2<float>::operator-() const;
template Vector2<double> Vector2<double>::operator-() const;

/* Vectors Operators: [Ax Ay]+[Bx By] = [Ax+Bx Ay+By] */
template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
    return Vector2<T>(x + other.x, y + other.y);
}
template Vector2<int> Vector2<int>::operator+(const Vector2<int>& other) const;
template Vector2<float> Vector2<float>::operator+(const Vector2<float>& other) const;
template Vector2<double> Vector2<double>::operator+(const Vector2<double>& other) const;

/* Vectors Operators: [Ax Ay]-[Bx By] = [Ax-Bx Ay-By] */
template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y);
}
template Vector2<int> Vector2<int>::operator-(const Vector2<int>& other) const;
template Vector2<float> Vector2<float>::operator-(const Vector2<float>& other) const;
template Vector2<double> Vector2<double>::operator-(const Vector2<double>& other) const;

/* Scalars Operators [Ax Ay]*X = [Ax*X Ay*X] */
template <typename T>
Vector2<T> Vector2<T>::operator*(const T& other) const {
    return Vector2<T>(x * other, y * other);
}
template Vector2<int> Vector2<int>::operator*(const int& other) const;
template Vector2<float> Vector2<float>::operator*(const float& other) const;
template Vector2<double> Vector2<double>::operator*(const double& other) const;

/* Scalars Operators [Ax Ay]/X = [Ax/X Ay/X] */
template <typename T>
Vector2<T> Vector2<T>::operator/(const T& other) const {
    return Vector2<T>(x / other, y / other);
}
template Vector2<int> Vector2<int>::operator/(const int& other) const;
template Vector2<float> Vector2<float>::operator/(const float& other) const;
template Vector2<double> Vector2<double>::operator/(const double& other) const;

/* Comparison Operators: [Ax Ay] == [Bx By] */
template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& other) const {
    if (x != other.x) { return false; }
    if (y != other.y) { return false; }
    return true;
}
template bool Vector2<int>::operator==(const Vector2<int>& other) const;
template bool Vector2<float>::operator==(const Vector2<float>& other) const;
template bool Vector2<double>::operator==(const Vector2<double>& other) const;

/* Comparison Operators: [Ax Ay] != [Bx By] */
template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& other) const {
    return !operator==(other);
}
template bool Vector2<int>::operator!=(const Vector2<int>& other) const;
template bool Vector2<float>::operator!=(const Vector2<float>& other) const;
template bool Vector2<double>::operator!=(const Vector2<double>& other) const;

/* Default Constructor */
template <typename T>
Vector2<T>::Vector2() {
    x = T();
    y = T();
}
template Vector2<int>::Vector2();
template Vector2<float>::Vector2();
template Vector2<double>::Vector2();

/* Default Destructor */
template <typename T>
Vector2<T>::~Vector2() { }
template Vector2<int>::~Vector2();
template Vector2<float>::~Vector2();
template Vector2<double>::~Vector2();

/* Builder Constructor */
template <typename T>
Vector2<T>::Vector2(const T& _x, const T& _y) {
    x = _x;
    y = _y;
}
template Vector2<int>::Vector2(const int& x, const int& y);
template Vector2<float>::Vector2(const float& x, const float& y);
template Vector2<double>::Vector2(const double& x, const double& y);

/* Vector2 length: ||A|| = size = sqrt(Ax*Ax + Ay*Ay) */
template <typename T>
T Vector2<T>::magnitude() const {
    return std::sqrt(Vector2<T>::dot(*this, *this));
}
template int Vector2<int>::magnitude() const;
template float Vector2<float>::magnitude() const;
template double Vector2<double>::magnitude() const;

/* Vector2 length Squared: size*size = Ax*Ax + Ay*Ay */
template <typename T>
T Vector2<T>::magnitude_squared() const {
    return Vector2<T>::dot(*this, *this);
}
template int Vector2<int>::magnitude_squared() const;
template float Vector2<float>::magnitude_squared() const;
template double Vector2<double>::magnitude_squared() const;

/* Duplication Method */
template <typename T>
Vector2<T> Vector2<T>::clone() const {
    return Vector2<T>(x, y);
}
template Vector2<int> Vector2<int>::clone() const;
template Vector2<float> Vector2<float>::clone() const;
template Vector2<double> Vector2<double>::clone() const;

/* Normalize vector = [Ax Ay].(1/size) = [Ax/size Ay/size] */
template <typename T>
Vector2<T> Vector2<T>::normalize() const {
    T m = magnitude();
    if (m == T()) { return Vector2<T>(); }  // Avoid dividing by 0
    return Vector2<T>(x / m, y / m);
}
template Vector2<int> Vector2<int>::normalize() const;
template Vector2<float> Vector2<float>::normalize() const;
template Vector2<double> Vector2<double>::normalize() const;

/* Scale vector: [Ax Ay].scale = [Ax*scale Ay*scale] */
template <typename T>
Vector2<T> Vector2<T>::scale(const T& scale) const {
    return Vector2<T>(x * scale, y * scale);
}
template Vector2<int> Vector2<int>::scale(const int& scale) const;
template Vector2<float> Vector2<float>::scale(const float& scale) const;
template Vector2<double> Vector2<double>::scale(const double& scale) const;

/* Power vector: [Ax Ay]^pow = [Ax^pow Ay^pow] */
template <typename T>
Vector2<T> Vector2<T>::pow(const int& power) const {
    Vector2<T> temp = clone();
    for (int i = 0; i < power - 1; i++) {
        temp.x = temp.x * temp.x;
        temp.y = temp.y * temp.y;
    }
    return temp;
}

/* Rotate vector: [Ax Ay] = [Ax*cos(theta)-Ay*sin(theta) Ax*sin(theta)+Ay*cos(theta)] */
template <typename T>
Vector2<T> Vector2<T>::rotate(const float& angle) const {
    float theta = com::degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    return Vector2<T>(x * cos_theta - y * sin_theta, x * sin_theta + y * cos_theta);
}
template Vector2<int> Vector2<int>::rotate(const float& angle) const;
template Vector2<float> Vector2<float>::rotate(const float& angle) const;
template Vector2<double> Vector2<double>::rotate(const float& angle) const;

/* Set the angle: [Ax Ay] = [scale*cos(theta), scale*sin(theta)] */
template <typename T>
Vector2<T> Vector2<T>::set_angle(const float& angle) const {
    float theta = com::degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    T m = magnitude();
    return Vector2<T>(m * cos_theta, m * sin_theta);
}
template Vector2<int> Vector2<int>::set_angle(const float& angle) const;
template Vector2<float> Vector2<float>::set_angle(const float& angle) const;
template Vector2<double> Vector2<double>::set_angle(const float& angle) const;

/* Dot product: [Ax Ay].[Bx By] = (Ax)(Bx)+(Ay)(By) = Amag*Bmag*cos(theta) */
template <typename T>
T Vector2<T>::dot(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
template int Vector2<int>::dot(const Vector2<int>& v1, const Vector2<int>& v2);
template float Vector2<float>::dot(const Vector2<float>& v1, const Vector2<float>& v2);
template double Vector2<double>::dot(const Vector2<double>& v1, const Vector2<double>& v2);

/* Perp/Cross Dot product: [Ax Ay].[Bx By] = (Ax)(By)-(Ay)(Bx) = Amag*Bmag*sin(theta) */
template <typename T>
T Vector2<T>::cross(const Vector2<T>& v1, const Vector2<T>& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}
template int Vector2<int>::cross(const Vector2<int>& v1, const Vector2<int>& v2);
template float Vector2<float>::cross(const Vector2<float>& v1, const Vector2<float>& v2);
template double Vector2<double>::cross(const Vector2<double>& v1, const Vector2<double>& v2);

/* Normal of the Vector2: [-Ay, Ax] */
template <typename T>
Vector2<T> Vector2<T>::normal(const Vector2<T>& v1) {
    return Vector2<T>(-v1.y, v1.x);
}
template Vector2<int> Vector2<int>::normal(const Vector2<int>& v1);
template Vector2<float> Vector2<float>::normal(const Vector2<float>& v1);
template Vector2<double> Vector2<double>::normal(const Vector2<double>& v1);

/* Inverted Normal of the Vector2: [Ay, -Ax] */
template <typename T>
Vector2<T> Vector2<T>::normal_inverted(const Vector2<T>& v1) {
    return Vector2<T>(v1.y, -v1.x);
}
template Vector2<int> Vector2<int>::normal_inverted(const Vector2<int>& v1);
template Vector2<float> Vector2<float>::normal_inverted(const Vector2<float>& v1);
template Vector2<double> Vector2<double>::normal_inverted(const Vector2<double>& v1);

/* Normal of the Angle: [Ay - By, Bx - Ax] (normal from the wall as if vectors were deflected in a mirror) */
template <typename T>
Vector2<T> Vector2<T>::normal(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.y - v2.y, v2.x - v1.x);
}
template Vector2<int> Vector2<int>::normal(const Vector2<int>& v1, const Vector2<int>& v2);
template Vector2<float> Vector2<float>::normal(const Vector2<float>& v1, const Vector2<float>& v2);
template Vector2<double> Vector2<double>::normal(const Vector2<double>& v1, const Vector2<double>& v2);

/* Inverse Normal of the Angle: [By - Ay, Ax - Bx] (normal towards the wall as if vectors were deflected in a mirror) */
template <typename T>
Vector2<T> Vector2<T>::normal_inverted(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v2.y - v1.y, v1.x - v2.x);
}
template Vector2<int> Vector2<int>::normal_inverted(const Vector2<int>& v1, const Vector2<int>& v2);
template Vector2<float> Vector2<float>::normal_inverted(const Vector2<float>& v1, const Vector2<float>& v2);
template Vector2<double> Vector2<double>::normal_inverted(const Vector2<double>& v1, const Vector2<double>& v2);

/* Angle from a line: atan2(y, x) = Arg(x+iy) rad <=> atan2(y, x)*(180/PI)= Arg(x+iy) deg */
template <typename T>
T Vector2<T>::bearing(const Vector2<T>& v1, const Vector2<T>& v2) {
    return std::atan2(v1.y - v2.y, v1.x - v2.x) * (180 / PI);
}
template int Vector2<int>::bearing(const Vector2<int>& v1, const Vector2<int>& v2);
template float Vector2<float>::bearing(const Vector2<float>& v1, const Vector2<float>& v2);
template double Vector2<double>::bearing(const Vector2<double>& v1, const Vector2<double>& v2);

/* Compute the angle formed by 3 points */
template <typename T>
T Vector2<T>::angle(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3) {
    Vector2<T> v12 = v2 - v1;
    Vector2<T> v32 = v2 - v3;
    return std::atan2(Vector2<T>::cross(v12, v32), Vector2<T>::dot(v12, v32)) * (180 / PI);
}
template int Vector2<int>::angle(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3);
template float Vector2<float>::angle(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3);
template double Vector2<double>::angle(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3);

/* Vector2 length: ||A|| = size = sqrt(Ax*Ax + Ay*Ay) */
template <typename T>
T Vector2<T>::distance(const Vector2<T>& v1, const Vector2<T>& v2) {
    return std::sqrt(Vector2::dot(v1 - v2, v1 - v2));
}
template int Vector2<int>::distance(const Vector2<int>& v1, const Vector2<int>& v2);
template float Vector2<float>::distance(const Vector2<float>& v1, const Vector2<float>& v2);
template double Vector2<double>::distance(const Vector2<double>& v1, const Vector2<double>& v2);

/* Vector2 length Squared: size*size = Ax*Ax + Ay*Ay */
template <typename T>
T Vector2<T>::distance_squared(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2::dot(v1 - v2, v1 - v2);
}
template int Vector2<int>::distance_squared(const Vector2<int>& v1, const Vector2<int>& v2);
template float Vector2<float>::distance_squared(const Vector2<float>& v1, const Vector2<float>& v2);
template double Vector2<double>::distance_squared(const Vector2<double>& v1, const Vector2<double>& v2);

/* Rotate the point A around the point B by the angle in degree */
template <typename T>
Vector2<T> Vector2<T>::rotate_point(const Vector2<T>& v1, const Vector2<T>& v2, const float& angle) {
    return ((v2 - v1).rotate(angle) + v1);  // Rotate then Translate the point back to it's origin
}
template Vector2<int> Vector2<int>::rotate_point(const Vector2<int>& v1, const Vector2<int>& v2, const float& angle);
template Vector2<float> Vector2<float>::rotate_point(const Vector2<float>& v1, const Vector2<float>& v2, const float& angle);
template Vector2<double> Vector2<double>::rotate_point(const Vector2<double>& v1, const Vector2<double>& v2, const float& angle);

/* Compute the mirrored point from A to the line B */
template <typename T>
Vector2<T> Vector2<T>::mirrored_point(const Vector2<T>& v1, const Vector2<T>& v2) {
    return (Vector2<T>::line_projection(v1, v2) * T(2)) - v1;
}
template Vector2<int> Vector2<int>::mirrored_point(const Vector2<int>& v1, const Vector2<int>& v2);
template Vector2<float> Vector2<float>::mirrored_point(const Vector2<float>& v1, const Vector2<float>& v2);
template Vector2<double> Vector2<double>::mirrored_point(const Vector2<double>& v1, const Vector2<double>& v2);

/* Given the collinears points A,B and C, check if the point C lies on the line segment [AB] */
template <typename T>
bool Vector2<T>::point_on_segment(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3) {
    if (v3.x > std::max(v1.x, v2.x)) { return false; }
    if (v3.x < std::min(v1.x, v2.x)) { return false; }
    if (v3.y > std::max(v1.y, v2.y)) { return false; }
    if (v3.y < std::min(v1.y, v2.y)) { return false; }
    return true;
}
template bool Vector2<int>::point_on_segment(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3);
template bool Vector2<float>::point_on_segment(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3);
template bool Vector2<double>::point_on_segment(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3);

/* Find the orientation of the ordered triplet (A, B, C) */
/*
    return 0 => A,B and C Colinear: [AB] // [BC]
    return 1 => Clockwise Orientation: [BA] => [AC] => [CB]
    return 2 => Counter Clockwise: [AB] => [BC] => [CA]
*/
template <typename T>
int Vector2<T>::line_orientation(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3) {
    /*
        Using the segments slope: (By - Ay)*(Cx - Bx) - (Bx - Ax)*(Cy - By)
        - if the two slopes are equals, the segments are colinears
        - if slope[AB] > slope[BC], the orientation is clockwise
        - if slope[AB] < slope[BC], the orientation is counter clockwise
    */
    int sigma = static_cast<int>(Vector2<T>::cross(v2 - v1, v3 - v2));
    if (sigma == 0) { return 0; }
    if (sigma > 0) { return 1; }
    return 2;
}
template int Vector2<int>::line_orientation(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3);
template int Vector2<float>::line_orientation(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3);
template int Vector2<double>::line_orientation(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3);

/* Search if the segments AB and CD intersect */
template <typename T>
bool Vector2<T>::segments_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const Vector2<T>& v4) {
    int orientationA = Vector2<T>::line_orientation(v1, v2, v3);
    int orientationB = Vector2<T>::line_orientation(v1, v2, v4);
    int orientationC = Vector2<T>::line_orientation(v3, v4, v1);
    int orientationD = Vector2<T>::line_orientation(v3, v4, v2);

    // General case
    if (orientationA != orientationB && orientationC != orientationD) { return true; }
    if (orientationA == 0 && Vector2<T>::line_orientation(v1, v2, v3)) { return true; }
    if (orientationB == 0 && Vector2<T>::line_orientation(v1, v2, v4)) { return true; }
    if (orientationC == 0 && Vector2<T>::line_orientation(v3, v4, v1)) { return true; }
    if (orientationD == 0 && Vector2<T>::line_orientation(v3, v4, v2)) { return true; }
    return false;
}
template bool Vector2<int>::segments_intersect(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3, const Vector2<int>& v4);
template bool Vector2<float>::segments_intersect(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3, const Vector2<float>& v4);
template bool Vector2<double>::segments_intersect(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3, const Vector2<double>& v4);

/* Search if the lines AB and CD intersect */
template <typename T>
bool Vector2<T>::lines_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const Vector2<T>& v4) {
    T ABx = v1.x - v2.x;
    T ABy = v2.y - v1.y;
    T AB = ABy * v1.x + ABx * v1.y;

    T CDx = v3.x - v4.x;
    T CDy = v4.y - v3.y;
    T CD = CDy * v3.x + CDx * v3.y;

    // Det = 0 <=> Parallel Lines
    if (ABy * CDx - CDy * ABx == 0) { return false; }
    return true;
}
template bool Vector2<int>::lines_intersect(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3, const Vector2<int>& v4);
template bool Vector2<float>::lines_intersect(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3, const Vector2<float>& v4);
template bool Vector2<double>::lines_intersect(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3, const Vector2<double>& v4);

/* Test if the line segment [AB] intersect with the circle of center C and of radius size. Return true if collide and the collision point */
template <typename T>
std::pair<int, Vector2<T>> Vector2<T>::line_cercle_intersect(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3, const T& size) {
    // Check if one of the ends of the line segment (side) is inside the circle
    if (Vector2<T>::distance(v1, v3) < size) { return {2, v1}; }
    if (Vector2<T>::distance(v2, v3) < size) { return {3, v2}; }

    // Check if the closest point on the line is inside the circle
    Vector2<T> closest = Vector2<T>::segment_projection(v3, v1, v2);
    if (!Vector2<T>::point_on_segment(v1, v2, closest)) { return {0, Vector2<T>()}; }
    if (Vector2<T>::distance(closest, v3) <= size) { return {1, closest}; }

    return {0, Vector2<T>()};
}
template std::pair<int, Vector2<int>> Vector2<int>::line_cercle_intersect(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3, const int& size);
template std::pair<int, Vector2<float>> Vector2<float>::line_cercle_intersect(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3, const float& size);
template std::pair<int, Vector2<double>> Vector2<double>::line_cercle_intersect(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3, const double& size);

/* Project point A onto the line B */
template <typename T>
Vector2<T> Vector2<T>::line_projection(const Vector2<T>& v1, const Vector2<T>& v2) {
    T dp = Vector2<T>::dot(v1, v2);
    T bd = Vector2<T>::dot(v2, v2);
    if (bd == 0) { return Vector2<T>(); }
    return v2 * (dp / bd);
}
template Vector2<int> Vector2<int>::line_projection(const Vector2<int>& v1, const Vector2<int>& v2);
template Vector2<float> Vector2<float>::line_projection(const Vector2<float>& v1, const Vector2<float>& v2);
template Vector2<double> Vector2<double>::line_projection(const Vector2<double>& v1, const Vector2<double>& v2);

/* Projected point A onto the line BC */
template <typename T>
Vector2<T> Vector2<T>::segment_projection(const Vector2<T>& v1, const Vector2<T>& v2, const Vector2<T>& v3) {
    Vector2<T> vect_bc = v3 - v2;
    Vector2<T> vect_ba = v1 - v2;

    T dp = Vector2<T>::dot(vect_bc, vect_ba);
    T bd = Vector2<T>::dot(vect_bc, vect_bc);
    if (bd == T(0)) { return Vector2<T>(); }
    return v2 + vect_bc * (dp / bd);
}
template Vector2<int> Vector2<int>::segment_projection(const Vector2<int>& v1, const Vector2<int>& v2, const Vector2<int>& v3);
template Vector2<float> Vector2<float>::segment_projection(const Vector2<float>& v1, const Vector2<float>& v2, const Vector2<float>& v3);
template Vector2<double> Vector2<double>::segment_projection(const Vector2<double>& v1, const Vector2<double>& v2, const Vector2<double>& v3);

}  // namespace gmt

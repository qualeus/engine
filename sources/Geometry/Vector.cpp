#include "../../include/Geometry/Vector.hpp"

namespace gmt {

/* Vectors Operators: +[Ax Ay] = [Ax Ay] */
template <typename T>
Vector<T> Vector<T>::operator+() const {
    return Vector<T>(this->x, this->y);
}
template Vector<int> Vector<int>::operator+() const;
template Vector<float> Vector<float>::operator+() const;
template Vector<double> Vector<double>::operator+() const;

/* Vectors Operators: -[Ax Ay] = [-Ax -Ay] */
template <typename T>
Vector<T> Vector<T>::operator-() const {
    return Vector<T>(-this->x, -this->y);
}
template Vector<int> Vector<int>::operator-() const;
template Vector<float> Vector<float>::operator-() const;
template Vector<double> Vector<double>::operator-() const;

/* Vectors Operators: [Ax Ay]+[Bx By] = [Ax+Bx Ay+By] */
template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    return Vector<T>(this->x + other.x, this->y + other.y);
}
template Vector<int> Vector<int>::operator+(const Vector<int>& other) const;
template Vector<float> Vector<float>::operator+(const Vector<float>& other) const;
template Vector<double> Vector<double>::operator+(const Vector<double>& other) const;

/* Vectors Operators: [Ax Ay]-[Bx By] = [Ax-Bx Ay-By] */
template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    return Vector<T>(this->x - other.x, this->y - other.y);
}
template Vector<int> Vector<int>::operator-(const Vector<int>& other) const;
template Vector<float> Vector<float>::operator-(const Vector<float>& other) const;
template Vector<double> Vector<double>::operator-(const Vector<double>& other) const;

/* Scalars Operators [Ax Ay]*X = [Ax*X Ay*X] */
template <typename T>
Vector<T> Vector<T>::operator*(const T& other) const {
    return Vector<T>(this->x * other, this->y * other);
}
template Vector<int> Vector<int>::operator*(const int& other) const;
template Vector<float> Vector<float>::operator*(const float& other) const;
template Vector<double> Vector<double>::operator*(const double& other) const;

/* Scalars Operators [Ax Ay]/X = [Ax/X Ay/X] */
template <typename T>
Vector<T> Vector<T>::operator/(const T& other) const {
    return Vector<T>(this->x / other, this->y / other);
}
template Vector<int> Vector<int>::operator/(const int& other) const;
template Vector<float> Vector<float>::operator/(const float& other) const;
template Vector<double> Vector<double>::operator/(const double& other) const;

/* Comparison Operators: [Ax Ay] == [Bx By] */
template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (this->x != other.x) { return false; }
    if (this->y != other.y) { return false; }
    return true;
}
template bool Vector<int>::operator==(const Vector<int>& other) const;
template bool Vector<float>::operator==(const Vector<float>& other) const;
template bool Vector<double>::operator==(const Vector<double>& other) const;

/* Comparison Operators: [Ax Ay] != [Bx By] */
template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
    return !this->operator==(other);
}
template bool Vector<int>::operator!=(const Vector<int>& other) const;
template bool Vector<float>::operator!=(const Vector<float>& other) const;
template bool Vector<double>::operator!=(const Vector<double>& other) const;

/* Default Constructor */
template <typename T>
Vector<T>::Vector() {
    this->x = T();
    this->y = T();
}
template Vector<int>::Vector();
template Vector<float>::Vector();
template Vector<double>::Vector();

/* Default Destructor */
template <typename T>
Vector<T>::~Vector() {}
template Vector<int>::~Vector();
template Vector<float>::~Vector();
template Vector<double>::~Vector();

/* Builder Constructor */
template <typename T>
Vector<T>::Vector(const T& x, const T& y) {
    this->x = x;
    this->y = y;
}
template Vector<int>::Vector(const int& x, const int& y);
template Vector<float>::Vector(const float& x, const float& y);
template Vector<double>::Vector(const double& x, const double& y);

/* Vector length: ||A|| = size = sqrt(Ax*Ax + Ay*Ay) */
template <typename T>
T Vector<T>::Magnitude() const {
    return std::sqrt(Vector<T>::Dot(*this, *this));
}
template int Vector<int>::Magnitude() const;
template float Vector<float>::Magnitude() const;
template double Vector<double>::Magnitude() const;

/* Vector length Squared: size*size = Ax*Ax + Ay*Ay */
template <typename T>
T Vector<T>::MagnitudeSquared() const {
    return Vector<T>::Dot(*this, *this);
}
template int Vector<int>::MagnitudeSquared() const;
template float Vector<float>::MagnitudeSquared() const;
template double Vector<double>::MagnitudeSquared() const;

/* Duplication Method */
template <typename T>
Vector<T> Vector<T>::Clone() const {
    return Vector<T>(this->x, this->y);
}
template Vector<int> Vector<int>::Clone() const;
template Vector<float> Vector<float>::Clone() const;
template Vector<double> Vector<double>::Clone() const;

/* Normalize vector = [Ax Ay].(1/size) = [Ax/size Ay/size] */
template <typename T>
Vector<T> Vector<T>::Normalize() const {
    T magnitude = this->Magnitude();
    if (magnitude == T()) { return Vector<T>(); }  // Avoid dividing by 0
    return Vector<T>(this->x / magnitude, this->y / magnitude);
}
template Vector<int> Vector<int>::Normalize() const;
template Vector<float> Vector<float>::Normalize() const;
template Vector<double> Vector<double>::Normalize() const;

/* Scale vector: [Ax Ay].scale = [Ax*scale Ay*scale] */
template <typename T>
Vector<T> Vector<T>::Scale(const T& scale) const {
    return Vector<T>(this->x * scale, this->y * scale);
}
template Vector<int> Vector<int>::Scale(const int& scale) const;
template Vector<float> Vector<float>::Scale(const float& scale) const;
template Vector<double> Vector<double>::Scale(const double& scale) const;

/* Power vector: [Ax Ay]^pow = [Ax^pow Ay^pow] */
template <typename T>
Vector<T> Vector<T>::Pow(const int& power) const {
    Vector<T> temp = this->Clone();
    for (int i = 0; i < power - 1; i++) {
        temp.x = temp.x * temp.x;
        temp.y = temp.y * temp.y;
    }
    return temp;
}

/* Rotate vector: [Ax Ay] = [Ax*cos(theta)-Ay*sin(theta) Ax*sin(theta)+Ay*cos(theta)] */
template <typename T>
Vector<T> Vector<T>::Rotate(const float& angle) const {
    float theta = com::degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    return Vector<T>(this->x * cos_theta - this->y * sin_theta, this->x * sin_theta + this->y * cos_theta);
}
template Vector<int> Vector<int>::Rotate(const float& angle) const;
template Vector<float> Vector<float>::Rotate(const float& angle) const;
template Vector<double> Vector<double>::Rotate(const float& angle) const;

/* Set the angle: [Ax Ay] = [scale*cos(theta), scale*sin(theta)] */
template <typename T>
Vector<T> Vector<T>::SetAngle(const float& angle) const {
    float theta = com::degree_to_radian(angle);
    float cos_theta = std::cos(theta);
    float sin_theta = std::sin(theta);
    T magnitude = this->Magnitude();
    return Vector<T>(magnitude * cos_theta, magnitude * sin_theta);
}
template Vector<int> Vector<int>::SetAngle(const float& angle) const;
template Vector<float> Vector<float>::SetAngle(const float& angle) const;
template Vector<double> Vector<double>::SetAngle(const float& angle) const;

/* Dot product: [Ax Ay].[Bx By] = (Ax)(Bx)+(Ay)(By) = Amag*Bmag*cos(theta) */
template <typename T>
T Vector<T>::Dot(const Vector<T>& v1, const Vector<T>& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}
template int Vector<int>::Dot(const Vector<int>& v1, const Vector<int>& v2);
template float Vector<float>::Dot(const Vector<float>& v1, const Vector<float>& v2);
template double Vector<double>::Dot(const Vector<double>& v1, const Vector<double>& v2);

/* Perp/Cross Dot product: [Ax Ay].[Bx By] = (Ax)(By)-(Ay)(Bx) = Amag*Bmag*sin(theta) */
template <typename T>
T Vector<T>::Cross(const Vector<T>& v1, const Vector<T>& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}
template int Vector<int>::Cross(const Vector<int>& v1, const Vector<int>& v2);
template float Vector<float>::Cross(const Vector<float>& v1, const Vector<float>& v2);
template double Vector<double>::Cross(const Vector<double>& v1, const Vector<double>& v2);

/* Normal of the Vector: [-Ay, Ax] */
template <typename T>
Vector<T> Vector<T>::Normal(const Vector<T>& v1) {
    return Vector<T>(-v1.y, v1.x);
}
template Vector<int> Vector<int>::Normal(const Vector<int>& v1);
template Vector<float> Vector<float>::Normal(const Vector<float>& v1);
template Vector<double> Vector<double>::Normal(const Vector<double>& v1);

/* Inverted Normal of the Vector: [Ay, -Ax] */
template <typename T>
Vector<T> Vector<T>::NormalInverted(const Vector<T>& v1) {
    return Vector<T>(v1.y, -v1.x);
}
template Vector<int> Vector<int>::NormalInverted(const Vector<int>& v1);
template Vector<float> Vector<float>::NormalInverted(const Vector<float>& v1);
template Vector<double> Vector<double>::NormalInverted(const Vector<double>& v1);

/* Normal of the Angle: [Ay - By, Bx - Ax] (normal from the wall as if vectors were deflected in a mirror) */
template <typename T>
Vector<T> Vector<T>::Normal(const Vector<T>& v1, const Vector<T>& v2) {
    return Vector<T>(v1.y - v2.y, v2.x - v1.x);
}
template Vector<int> Vector<int>::Normal(const Vector<int>& v1, const Vector<int>& v2);
template Vector<float> Vector<float>::Normal(const Vector<float>& v1, const Vector<float>& v2);
template Vector<double> Vector<double>::Normal(const Vector<double>& v1, const Vector<double>& v2);

/* Inverse Normal of the Angle: [By - Ay, Ax - Bx] (normal towards the wall as if vectors were deflected in a mirror) */
template <typename T>
Vector<T> Vector<T>::NormalInverted(const Vector<T>& v1, const Vector<T>& v2) {
    return Vector<T>(v2.y - v1.y, v1.x - v2.x);
}
template Vector<int> Vector<int>::NormalInverted(const Vector<int>& v1, const Vector<int>& v2);
template Vector<float> Vector<float>::NormalInverted(const Vector<float>& v1, const Vector<float>& v2);
template Vector<double> Vector<double>::NormalInverted(const Vector<double>& v1, const Vector<double>& v2);

/* Angle from a line: atan2(y, x) = Arg(x+iy) rad <=> atan2(y, x)*(180/PI)= Arg(x+iy) deg */
template <typename T>
T Vector<T>::Bearing(const Vector<T>& v1, const Vector<T>& v2) {
    return std::atan2(v1.y - v2.y, v1.x - v2.x) * (180 / PI);
}
template int Vector<int>::Bearing(const Vector<int>& v1, const Vector<int>& v2);
template float Vector<float>::Bearing(const Vector<float>& v1, const Vector<float>& v2);
template double Vector<double>::Bearing(const Vector<double>& v1, const Vector<double>& v2);

/* Compute the angle formed by 3 points */
template <typename T>
T Vector<T>::Angle(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3) {
    Vector<T> v12 = v2 - v1;
    Vector<T> v32 = v2 - v3;
    return std::atan2(Vector<T>::Cross(v12, v32), Vector<T>::Dot(v12, v32)) * (180 / PI);
}
template int Vector<int>::Angle(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3);
template float Vector<float>::Angle(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3);
template double Vector<double>::Angle(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3);

/* Vector length: ||A|| = size = sqrt(Ax*Ax + Ay*Ay) */
template <typename T>
T Vector<T>::Distance(const Vector<T>& v1, const Vector<T>& v2) {
    return std::sqrt(Vector::Dot(v1 - v2, v1 - v2));
}
template int Vector<int>::Distance(const Vector<int>& v1, const Vector<int>& v2);
template float Vector<float>::Distance(const Vector<float>& v1, const Vector<float>& v2);
template double Vector<double>::Distance(const Vector<double>& v1, const Vector<double>& v2);

/* Vector length Squared: size*size = Ax*Ax + Ay*Ay */
template <typename T>
T Vector<T>::DistanceSquared(const Vector<T>& v1, const Vector<T>& v2) {
    return Vector::Dot(v1 - v2, v1 - v2);
}
template int Vector<int>::DistanceSquared(const Vector<int>& v1, const Vector<int>& v2);
template float Vector<float>::DistanceSquared(const Vector<float>& v1, const Vector<float>& v2);
template double Vector<double>::DistanceSquared(const Vector<double>& v1, const Vector<double>& v2);

/* Rotate the point A around the point B by the angle in degree */
template <typename T>
Vector<T> Vector<T>::RotatePoint(const Vector<T>& v1, const Vector<T>& v2, const float& angle) {
    return ((v2 - v1).Rotate(angle) + v1);  // Rotate then Translate the point back to it's origin
}
template Vector<int> Vector<int>::RotatePoint(const Vector<int>& v1, const Vector<int>& v2, const float& angle);
template Vector<float> Vector<float>::RotatePoint(const Vector<float>& v1, const Vector<float>& v2, const float& angle);
template Vector<double> Vector<double>::RotatePoint(const Vector<double>& v1, const Vector<double>& v2, const float& angle);

/* Compute the mirrored point from A to the line B */
template <typename T>
Vector<T> Vector<T>::MirroredPoint(const Vector<T>& v1, const Vector<T>& v2) {
    return (Vector<T>::LineProjection(v1, v2) * T(2)) - v1;
}
template Vector<int> Vector<int>::MirroredPoint(const Vector<int>& v1, const Vector<int>& v2);
template Vector<float> Vector<float>::MirroredPoint(const Vector<float>& v1, const Vector<float>& v2);
template Vector<double> Vector<double>::MirroredPoint(const Vector<double>& v1, const Vector<double>& v2);

/* Given the collinears points A,B and C, check if the point C lies on the line segment [AB] */
template <typename T>
bool Vector<T>::PointOnSegment(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3) {
    if (v3.x > std::max(v1.x, v2.x)) { return false; }
    if (v3.x < std::min(v1.x, v2.x)) { return false; }
    if (v3.y > std::max(v1.y, v2.y)) { return false; }
    if (v3.y < std::min(v1.y, v2.y)) { return false; }
    return true;
}
template bool Vector<int>::PointOnSegment(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3);
template bool Vector<float>::PointOnSegment(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3);
template bool Vector<double>::PointOnSegment(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3);

/* Find the orientation of the ordered triplet (A, B, C) */
/*
    return 0 => A,B and C Colinear: [AB] // [BC]
    return 1 => Clockwise Orientation: [BA] => [AC] => [CB]
    return 2 => Counter Clockwise: [AB] => [BC] => [CA]
*/
template <typename T>
int Vector<T>::LineOrientation(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3) {
    /*
        Using the segments slope: (By - Ay)*(Cx - Bx) - (Bx - Ax)*(Cy - By)
        - if the two slopes are equals, the segments are colinears
        - if slope[AB] > slope[BC], the orientation is clockwise
        - if slope[AB] < slope[BC], the orientation is counter clockwise
    */
    int sigma = static_cast<int>(Vector<T>::Cross(v2 - v1, v3 - v2));
    if (sigma == 0) { return 0; }
    if (sigma > 0) { return 1; }
    return 2;
}
template int Vector<int>::LineOrientation(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3);
template int Vector<float>::LineOrientation(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3);
template int Vector<double>::LineOrientation(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3);

/* Search if the segments AB and CD intersect */
template <typename T>
bool Vector<T>::SegmentsIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const Vector<T>& v4) {
    int orientationA = Vector<T>::LineOrientation(v1, v2, v3);
    int orientationB = Vector<T>::LineOrientation(v1, v2, v4);
    int orientationC = Vector<T>::LineOrientation(v3, v4, v1);
    int orientationD = Vector<T>::LineOrientation(v3, v4, v2);

    // General case
    if (orientationA != orientationB && orientationC != orientationD) { return true; }
    if (orientationA == 0 && Vector<T>::LineOrientation(v1, v2, v3)) { return true; }
    if (orientationB == 0 && Vector<T>::LineOrientation(v1, v2, v4)) { return true; }
    if (orientationC == 0 && Vector<T>::LineOrientation(v3, v4, v1)) { return true; }
    if (orientationD == 0 && Vector<T>::LineOrientation(v3, v4, v2)) { return true; }
    return false;
}
template bool Vector<int>::SegmentsIntersect(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3, const Vector<int>& v4);
template bool Vector<float>::SegmentsIntersect(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3, const Vector<float>& v4);
template bool Vector<double>::SegmentsIntersect(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3, const Vector<double>& v4);

/* Search if the lines AB and CD intersect */
template <typename T>
bool Vector<T>::LinesIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const Vector<T>& v4) {
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
template bool Vector<int>::LinesIntersect(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3, const Vector<int>& v4);
template bool Vector<float>::LinesIntersect(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3, const Vector<float>& v4);
template bool Vector<double>::LinesIntersect(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3, const Vector<double>& v4);

/* Test if the line segment [AB] intersect with the circle of center C and of radius size. Return true if collide and the collision point */
template <typename T>
std::pair<int, Vector<T>> Vector<T>::LineCercleIntersect(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3, const T& size) {
    // Check if one of the ends of the line segment (side) is inside the circle
    if (Vector<T>::Distance(v1, v3) < size) { return {2, v1}; }
    if (Vector<T>::Distance(v2, v3) < size) { return {3, v2}; }

    // Check if the closest point on the line is inside the circle
    Vector<T> closest = Vector<T>::SegmentProjection(v3, v1, v2);
    if (!Vector<T>::PointOnSegment(v1, v2, closest)) { return {0, Vector<T>()}; }
    if (Vector<T>::Distance(closest, v3) <= size) { return {1, closest}; }

    return {0, Vector<T>()};
}
template std::pair<int, Vector<int>> Vector<int>::LineCercleIntersect(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3, const int& size);
template std::pair<int, Vector<float>> Vector<float>::LineCercleIntersect(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3, const float& size);
template std::pair<int, Vector<double>> Vector<double>::LineCercleIntersect(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3, const double& size);

/* Project point A onto the line B */
template <typename T>
Vector<T> Vector<T>::LineProjection(const Vector<T>& v1, const Vector<T>& v2) {
    T dp = Vector<T>::Dot(v1, v2);
    T bd = Vector<T>::Dot(v2, v2);
    if (bd == 0) { return Vector<T>(); }
    return v2 * (dp / bd);
}
template Vector<int> Vector<int>::LineProjection(const Vector<int>& v1, const Vector<int>& v2);
template Vector<float> Vector<float>::LineProjection(const Vector<float>& v1, const Vector<float>& v2);
template Vector<double> Vector<double>::LineProjection(const Vector<double>& v1, const Vector<double>& v2);

/* Projected point A onto the line BC */
template <typename T>
Vector<T> Vector<T>::SegmentProjection(const Vector<T>& v1, const Vector<T>& v2, const Vector<T>& v3) {
    Vector<T> vect_bc = v3 - v2;
    Vector<T> vect_ba = v1 - v2;

    T dp = Vector<T>::Dot(vect_bc, vect_ba);
    T bd = Vector<T>::Dot(vect_bc, vect_bc);
    if (bd == T(0)) { return Vector<T>(); }
    return v2 + vect_bc * (dp / bd);
}
template Vector<int> Vector<int>::SegmentProjection(const Vector<int>& v1, const Vector<int>& v2, const Vector<int>& v3);
template Vector<float> Vector<float>::SegmentProjection(const Vector<float>& v1, const Vector<float>& v2, const Vector<float>& v3);
template Vector<double> Vector<double>::SegmentProjection(const Vector<double>& v1, const Vector<double>& v2, const Vector<double>& v3);

}  // namespace gmt

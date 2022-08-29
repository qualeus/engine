#include "../../include/Corpses/Edge.hpp"

namespace phy {

Edge::Edge() : Shape(gmt::UnitI(), gmt::UnitI(), gmt::UnitI()) {
    m_point_a = gmt::VectorI();
    m_point_b = gmt::VectorI();

    calibrate();
}

Edge::Edge(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::VectorI point_a, gmt::VectorI point_b) : Shape(mass, friction, damping) {
    m_point_a = point_a;
    m_point_b = point_b;

    calibrate();
}

Edge& Edge::operator=(const Edge& rhs) {
    Shape::operator=(rhs);
    m_point_a = rhs.get_point_a();
    m_point_b = rhs.get_point_b();
    return *this;
}

gmt::VectorI Edge::get_point_a() const {
    return m_point_a;
}
void Edge::set_point_a(const gmt::VectorI& point_a) {
    m_point_a = point_a;
}

gmt::VectorI Edge::get_point_b() const {
    return m_point_b;
}
void Edge::set_point_b(const gmt::VectorI& point_b) {
    m_point_b = point_b;
}

void Edge::calibrate() {
    m_centroid = (m_point_b - m_point_a) / gmt::UnitI(2);  // centered origin
    m_moment   = gmt::UnitI();                             // TODO find moment of inertia (no surface)
}

bool Edge::pointed(gmt::VectorI pos) const {
    return false;  // TODO
}

}  // namespace phy
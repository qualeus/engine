#include "../../include/Corpses/Circle.hpp"

namespace phy {

Circle::Circle() : Shape(gmt::UnitI(), gmt::UnitI(), gmt::UnitI()) {
    m_radius   = gmt::UnitI();
    m_centroid = gmt::VectorI();

    calibrate();
}

Circle::Circle(gmt::VectorI position, gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::UnitI radius) : Shape(mass, friction, damping) {
    m_radius   = radius;
    m_centroid = position;

    calibrate();
}

Circle& Circle::operator=(const Circle& rhs) {
    Shape::operator=(rhs);
    m_radius = rhs.get_radius();
    return *this;
}

gmt::UnitI Circle::get_radius() const {
    return m_radius;
}
void Circle::set_radius(const gmt::UnitI& radius) {
    m_radius = radius;
}

void Circle::calibrate() {
    //  m_centroid = m_centroid;                                       // centered origin
    m_moment = m_mass * (PI * std::pow(m_radius, 4)) / gmt::UnitI(4);  // I = (PI.R^4)/4
}

bool Circle::pointed(gmt::VectorI pos) const {
    return gmt::VectorI::distance(pos, m_centroid) < (m_radius / gmt::UnitI(2));
}

}  // namespace phy
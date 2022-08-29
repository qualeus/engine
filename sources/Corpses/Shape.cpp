#include "../../include/Corpses/Shape.hpp"

namespace phy {

Shape::Shape(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping) {
    m_mass     = mass;
    m_friction = friction;
    m_damping  = damping;

    m_moment   = gmt::UnitI();
    m_centroid = gmt::VectorI();
}

gmt::UnitI Shape::get_mass() const {
    return m_mass;
}
void Shape::set_mass(gmt::UnitI mass) {
    m_mass = mass;
}

gmt::UnitI Shape::get_friction() const {
    return m_friction;
}
void Shape::set_friction(gmt::UnitI friction) {
    m_friction = friction;
}

gmt::UnitI Shape::get_damping() const {
    return m_damping;
}
void Shape::set_damping(gmt::UnitI damping) {
    m_damping = damping;
}

gmt::UnitI Shape::get_moment() const {
    return m_moment;
}
void Shape::set_moment(gmt::UnitI moment) {
    m_moment = moment;
}

gmt::VectorI Shape::get_centroid() const {
    return m_centroid;
}
void Shape::set_centroid(gmt::VectorI centroid) {
    m_centroid = centroid;
}

}  // namespace phy
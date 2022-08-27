#include "../../include/Corpses/Circle.hpp"

namespace phy {

Circle::Circle(gmt::UnitI x,
               gmt::UnitI y,
               gmt::UnitI size,
               gmt::UnitI mass,
               gmt::UnitI damping,
               gmt::UnitI speed_x,
               gmt::UnitI speed_y,
               gmt::UnitI rotation,
               gmt::UnitI motor,
               bool fixed,
               bool tied,
               bool etherial)
    : Corpse(mass, damping, fixed, tied, etherial) {
    m_current_pos = gmt::VectorI(x, y);
    m_last_pos = gmt::VectorI(x - speed_x, y - speed_y);

    m_current_rotation = gmt::UnitI(0);
    m_last_rotation = rotation;

    m_size = size;
    m_motor = motor;

    m_bounds = gmt::BoundsI(get_pos_x() - get_size(), get_pos_y() - get_size(), get_pos_x() + get_size(), get_pos_y() + get_size());
}

Circle& Circle::operator=(const Circle& rhs) {
    Corpse::operator=(rhs);
    m_size = rhs.get_size();
    return *this;
}
// Circle::~Circle() {}

int Circle::get_class() const {
    return ID_CIRCLE;
}
int Circle::id_class() {
    return ID_CIRCLE;
}

void Circle::step() {
    if (m_fixed) {
        m_last_pos = m_current_pos;
    } else {
        gmt::VectorI diff_pos = m_current_pos - m_last_pos;
        m_last_pos = m_current_pos;
        drag(diff_pos);
    }

    if (m_tied) {
        m_last_rotation = std::fmod(m_current_rotation, gmt::UnitI(RO));
    } else {
        gmt::UnitI diff_rotation = m_current_rotation - m_last_rotation;
        m_last_rotation = m_current_rotation;
        rotate(diff_rotation);
    }

    // Update bounds
    update_bounds();

    // Add the motor rotation even if the object is tied
    // if (!gmt::decimal_equals(motor, gmt::UnitI(0), gmt::UnitI(0.0001))) { m_current_rotation = m_current_rotation + motor; }
}
void Circle::update_bounds() {
    m_bounds = gmt::BoundsI(get_pos_x() - get_size(), get_pos_y() - get_size(), get_pos_x() + get_size(), get_pos_y() + get_size());
}

void Circle::stop() {
    m_last_pos = m_current_pos;
}

void Circle::bloc() {
    m_last_rotation = m_current_rotation;
}

void Circle::move(const gmt::VectorI& move) {
    m_current_pos = move;
}

void Circle::drag(const gmt::VectorI& drag) {
    m_current_pos = m_current_pos + drag;
}

void Circle::turn(const gmt::UnitI& turn) {
    m_current_rotation = std::fmod(turn, gmt::UnitI(RO));
}

void Circle::rotate(const gmt::UnitI& rotate) {
    m_current_rotation = std::fmod(m_current_rotation + rotate, gmt::UnitI(RO));
}

bool Circle::in_bounds(const gmt::BoundsI& bounds) const {
    return gmt::BoundsI::bounds_in_bounds(get_bounds(), bounds);
}
bool Circle::pointed(const gmt::VectorI& point) const {
    return (gmt::VectorI::distance(get_pos(), point) <= m_size);
}

gmt::UnitI Circle::get_size() const {
    return m_size;
}
void Circle::set_size(const gmt::UnitI& size) {
    m_size = size;
}

}  // namespace phy
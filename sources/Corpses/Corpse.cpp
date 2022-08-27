#include "../../include/Corpses/Corpse.hpp"
namespace phy {

Corpse::Corpse(gmt::UnitI mass, gmt::UnitI damping, bool fixed, bool tied, bool etherial) {
    static int global_corpse_id = 0;
    m_id = global_corpse_id++;

    m_fixed = fixed;
    m_tied = tied;
    m_etherial = etherial;

    m_mass = mass;
    m_friction = gmt::UnitI(1);
    m_damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));

    m_bounds = gmt::BoundsI();
}

Corpse& Corpse::operator=(const Corpse& rhs) {
    m_id = rhs.get_id();

    m_fixed = rhs.get_fixed();
    m_tied = rhs.get_tied();
    m_etherial = rhs.get_etherial();

    m_mass = rhs.get_mass();
    m_friction = rhs.get_friction();
    m_damping = rhs.get_damping();

    m_current_pos = rhs.get_pos();
    m_last_pos = rhs.get_last_pos();
    m_propulsor = rhs.get_propulsor();

    m_current_rotation = rhs.get_rotation();
    m_last_rotation = rhs.get_last_rotation();
    m_motor = rhs.get_motor();

    m_bounds = rhs.get_bounds();

    return *this;
}
// Corpse::~Corpse() = default;

int Corpse::get_id() const {
    return m_id;
}
int Corpse::get_class() const {
    return ID_CORPSE;
}
static int id_class() {
    return ID_CORPSE;
}

bool Corpse::get_fixed() const {
    return m_fixed;
}
void Corpse::set_fixed(bool fixed) {
    m_fixed = fixed;
}

bool Corpse::get_etherial() const {
    return m_etherial;
}
void Corpse::set_etherial(bool etherial) {
    m_etherial = etherial;
}

bool Corpse::get_tied() const {
    return m_tied;
}
void Corpse::set_tied(bool tied) {
    m_tied = tied;
}

gmt::VectorI Corpse::get_pos() const {
    return m_current_pos;
}
gmt::UnitI Corpse::get_pos_x() const {
    return m_current_pos.x;
}
gmt::UnitI Corpse::get_pos_y() const {
    return m_current_pos.y;
}

void Corpse::set_pos(const gmt::VectorI& pos) {
    m_current_pos = pos;
}
void Corpse::set_pos_x(const gmt::UnitI& pos_x) {
    m_current_pos.x = pos_x;
}
void Corpse::set_pos_y(const gmt::UnitI& pos_y) {
    m_current_pos.y = pos_y;
}

gmt::VectorI Corpse::get_last_pos() const {
    return m_last_pos;
}
gmt::UnitI Corpse::get_last_pos_x() const {
    return m_last_pos.x;
}
gmt::UnitI Corpse::get_last_pos_y() const {
    return m_last_pos.y;
}

void Corpse::set_last_pos(const gmt::VectorI& pos) {
    m_last_pos = pos;
}
void Corpse::set_last_pos_x(const gmt::UnitI& pos_x) {
    m_last_pos.x = pos_x;
}
void Corpse::set_last_pos_y(const gmt::UnitI& pos_y) {
    m_last_pos.y = pos_y;
}

gmt::VectorI Corpse::get_diff_pos() const {
    return (get_pos() - get_last_pos());
}
gmt::UnitI Corpse::get_diff_pos_x() const {
    return (get_pos_x() - get_last_pos_x());
}
gmt::UnitI Corpse::get_diff_pos_y() const {
    return (get_pos_y() - get_last_pos_y());
}

gmt::VectorI Corpse::get_propulsor() const {
    return m_propulsor;
};
void Corpse::set_propulsor(const gmt::VectorI& propulsor) {
    m_propulsor = propulsor;
}

gmt::UnitI Corpse::get_rotation() const {
    return m_current_rotation;
}
void Corpse::set_rotation(const gmt::UnitI& current_rotation) {
    m_current_rotation = current_rotation;
}
gmt::UnitI Corpse::get_diff_rotation() const {
    return (get_rotation() - get_last_rotation());
}

gmt::UnitI Corpse::get_last_rotation() const {
    return m_last_rotation;
}
void Corpse::set_last_rotation(const gmt::UnitI& last_rotation) {
    m_last_rotation = last_rotation;
}

gmt::UnitI Corpse::get_motor() const {
    return m_motor;
}
void Corpse::set_motor(const gmt::UnitI& motor) {
    m_motor = motor;
}

void Corpse::set_damping(const gmt::UnitI& damping) {
    m_damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));
}

gmt::UnitI Corpse::get_damping() const {
    return m_damping;
}

gmt::UnitI Corpse::get_bounce() const {
    return gmt::UnitI(1) / m_damping;
}

gmt::UnitI Corpse::get_mass() const {
    return m_mass;
}

void Corpse::set_mass(const gmt::UnitI& mass) {
    m_mass = mass;
}

gmt::UnitI Corpse::get_friction() const {
    return m_friction;
}

void Corpse::set_friction(const gmt::UnitI& friction) {
    m_friction = friction;
}

gmt::BoundsI Corpse::get_bounds() const {
    return m_bounds;
}

bool Corpse::equals(const Corpse* other) {
    return get_id() == other->get_id();
}

inline bool Corpse::operator==(const Corpse* other) {
    return equals(other);
}

}  // namespace phy
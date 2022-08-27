#include "../../include/Constraints/Constraint.hpp"
namespace phy {
Constraint::Constraint(std::shared_ptr<phy::Corpse> corpse_a,
                       std::shared_ptr<phy::Corpse> corpse_b,
                       gmt::VectorI relative_pos_a,
                       gmt::VectorI relative_pos_b,
                       gmt::UnitI relative_angle_a,
                       gmt::UnitI relative_angle_b,
                       bool rotation_a,
                       bool rotation_b,
                       gmt::UnitI friction_a,
                       gmt::UnitI friction_b,
                       bool breaking) {
    static int global_constraint_id = 0;
    m_id = global_constraint_id++;

    m_corpse_a = corpse_a;
    m_corpse_b = corpse_b;

    m_relative_pos_a = relative_pos_a;
    m_relative_pos_b = relative_pos_b;

    m_relative_angle_a = relative_angle_a;
    m_relative_angle_b = relative_angle_b;

    m_rotation_a = rotation_a;
    m_rotation_b = rotation_b;

    m_friction_a = friction_a;
    m_friction_b = friction_b;

    m_breaking = breaking;
    m_broken = false;
}

int Constraint::get_id() const {
    return m_id;
}
int Constraint::get_class() const {
    return ID_CONSTRAINT;
}
static int id_class() {
    return ID_CONSTRAINT;
}

bool Constraint::equals(const Constraint* other) const {
    return get_id() == other->get_id();
}

Constraint& Constraint::operator=(const Constraint& rhs) {
    m_id = rhs.get_id();
    m_corpse_a = rhs.get_corpse_a();
    m_corpse_b = rhs.get_corpse_b();
    m_relative_pos_a = rhs.get_relative_pos_a();
    m_relative_pos_b = rhs.get_relative_pos_b();
    m_relative_angle_a = rhs.get_relative_angle_a();
    m_relative_angle_b = rhs.get_relative_angle_b();
    m_rotation_a = rhs.get_rotation_a();
    m_rotation_b = rhs.get_rotation_b();
    m_friction_a = rhs.get_friction_a();
    m_friction_b = rhs.get_friction_b();
    m_breaking = rhs.get_breaking();
    m_broken = rhs.get_broken();
    return *this;
}

inline bool Constraint::operator==(const Constraint* other) {
    return equals(other);
}

std::shared_ptr<phy::Corpse> Constraint::get_corpse_a() const {
    return m_corpse_a;
}

void Constraint::set_corpse_a(std::shared_ptr<phy::Corpse> corpse_a) {
    m_corpse_a = corpse_a;
}

std::shared_ptr<phy::Corpse> Constraint::get_corpse_b() const {
    return m_corpse_b;
}

void Constraint::set_corpse_b(std::shared_ptr<phy::Corpse> corpse_b) {
    m_corpse_b = corpse_b;
}

gmt::VectorI Constraint::get_relative_pos_a() const {
    return m_relative_pos_a;
}

void Constraint::set_relative_pos_a(gmt::VectorI relative_pos_a) {
    m_relative_pos_a = relative_pos_a;
}

gmt::VectorI Constraint::get_relative_pos_b() const {
    return m_relative_pos_b;
}

void Constraint::set_relative_pos_b(gmt::VectorI relative_pos_b) {
    m_relative_pos_b = relative_pos_b;
}

bool Constraint::get_rotation_a() const {
    return m_rotation_a;
}
void Constraint::set_rotation_a(bool rotation_a) {
    m_rotation_a = rotation_a;
}

bool Constraint::get_rotation_b() const {
    return m_rotation_b;
}

void Constraint::set_rotation_b(bool rotation_b) {
    m_rotation_b = rotation_b;
}

gmt::UnitI Constraint::get_relative_angle_a() const {
    return m_relative_angle_a;
}

void Constraint::set_relative_angle_a(gmt::UnitI relative_angle_a) {
    m_relative_angle_a = relative_angle_a;
}

gmt::UnitI Constraint::get_relative_angle_b() const {
    return m_relative_angle_b;
}

void Constraint::set_relative_angle_b(gmt::UnitI relative_angle_b) {
    m_relative_angle_b = relative_angle_b;
}

gmt::UnitI Constraint::get_friction_a() const {
    return m_friction_a;
}

void Constraint::set_friction_a(gmt::UnitI friction_a) {
    m_friction_a = friction_a;
}

gmt::UnitI Constraint::get_friction_b() const {
    return m_friction_b;
}

void Constraint::set_friction_b(gmt::UnitI friction_b) {
    m_friction_a = friction_b;
}

bool Constraint::get_breaking() const {
    return m_breaking;
}
void Constraint::set_breaking(bool breaking) {
    m_breaking = breaking;
}

bool Constraint::get_broken() const {
    return m_broken;
}

void Constraint::set_broken(bool broken) {
    m_broken = broken;
}

}  // namespace phy
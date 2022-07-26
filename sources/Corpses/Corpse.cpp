#include "../../include/Corpses/Corpse.hpp"
namespace phy {

Corpse::Corpse(gmt::UnitI mass, gmt::UnitI damping, bool fixed, bool tied, bool etherial) {
    static int global_corpse_id = 0;
    this->id = global_corpse_id++;

    this->fixed = fixed;
    this->tied = tied;
    this->etherial = etherial;

    this->mass = mass;
    this->friction = gmt::UnitI(1);
    this->damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));

    this->bounds = gmt::BoundsI();
}
Corpse& Corpse::operator=(const Corpse& rhs) {
    this->id = rhs.get_id();

    this->fixed = rhs.get_fixed();
    this->tied = rhs.get_tied();
    this->etherial = rhs.get_etherial();

    this->mass = rhs.get_mass();
    this->friction = rhs.get_friction();
    this->damping = rhs.get_damping();

    this->current_pos = rhs.get_pos();
    this->last_pos = rhs.get_last_pos();
    this->propulsor = rhs.get_propulsor();

    this->current_rotation = rhs.get_rotation();
    this->last_rotation = rhs.get_last_rotation();
    this->motor = rhs.get_motor();

    this->bounds = rhs.get_bounds();

    return *this;
}
// Corpse::~Corpse() = default;

int Corpse::get_id() const { return this->id; }
int Corpse::get_class() const { return ID_CORPSE; }
static int id_class() { return ID_CORPSE; }

bool Corpse::get_fixed() const { return this->fixed; }
void Corpse::set_fixed(bool fixed) { this->fixed = fixed; }

bool Corpse::get_etherial() const { return this->etherial; }
void Corpse::set_etherial(bool etherial) { this->etherial = etherial; }

bool Corpse::get_tied() const { return this->tied; }
void Corpse::set_tied(bool tied) { this->tied = tied; }

gmt::VectorI Corpse::get_pos() const { return this->current_pos; }
gmt::UnitI Corpse::get_pos_x() const { return this->current_pos.x; }
gmt::UnitI Corpse::get_pos_y() const { return this->current_pos.y; }

void Corpse::set_pos(const gmt::VectorI& pos) { this->current_pos = pos; }
void Corpse::set_pos_x(const gmt::UnitI& pos_x) { this->current_pos.x = pos_x; }
void Corpse::set_pos_y(const gmt::UnitI& pos_y) { this->current_pos.y = pos_y; }

gmt::VectorI Corpse::get_last_pos() const { return this->last_pos; }
gmt::UnitI Corpse::get_last_pos_x() const { return this->last_pos.x; }
gmt::UnitI Corpse::get_last_pos_y() const { return this->last_pos.y; }

void Corpse::set_last_pos(const gmt::VectorI& pos) { this->last_pos = pos; }
void Corpse::set_last_pos_x(const gmt::UnitI& pos_x) { this->last_pos.x = pos_x; }
void Corpse::set_last_pos_y(const gmt::UnitI& pos_y) { this->last_pos.y = pos_y; }

gmt::VectorI Corpse::get_diff_pos() const { return (this->get_pos() - this->get_last_pos()); }
gmt::UnitI Corpse::get_diff_pos_x() const { return (this->get_pos_x() - this->get_last_pos_x()); }
gmt::UnitI Corpse::get_diff_pos_y() const { return (this->get_pos_y() - this->get_last_pos_y()); }

gmt::VectorI Corpse::get_propulsor() const { return this->propulsor; };
void Corpse::set_propulsor(const gmt::VectorI& propulsor) { this->propulsor = propulsor; }

gmt::UnitI Corpse::get_rotation() const { return this->current_rotation; }
void Corpse::set_rotation(const gmt::UnitI& current_rotation) { this->current_rotation = current_rotation; }
gmt::UnitI Corpse::get_diff_rotation() const { return (this->get_rotation() - this->get_last_rotation()); }

gmt::UnitI Corpse::get_last_rotation() const { return this->last_rotation; }
void Corpse::set_last_rotation(const gmt::UnitI& last_rotation) { this->last_rotation = last_rotation; }

gmt::UnitI Corpse::get_motor() const { return this->motor; }
void Corpse::set_motor(const gmt::UnitI& motor) { this->motor = motor; }

void Corpse::set_damping(const gmt::UnitI& damping) { this->damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING)); }
gmt::UnitI Corpse::get_damping() const { return this->damping; }
gmt::UnitI Corpse::get_bounce() const { return gmt::UnitI(1) / this->damping; }

gmt::UnitI Corpse::get_mass() const { return this->mass; }
void Corpse::set_mass(const gmt::UnitI& mass) { this->mass = mass; }

gmt::UnitI Corpse::get_friction() const { return this->friction; }
void Corpse::set_friction(const gmt::UnitI& friction) { this->friction = friction; }

gmt::BoundsI Corpse::get_bounds() const { return this->bounds; }

bool Corpse::Equals(const Corpse* other) { return this->get_id() == other->get_id(); }

inline bool Corpse::operator==(const Corpse* other) { return this->Equals(other); }

}  // namespace phy
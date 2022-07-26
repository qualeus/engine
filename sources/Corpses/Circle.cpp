#include "../../include/Corpses/Circle.hpp"

namespace phy {

Circle::Circle(gmt::UnitI x, gmt::UnitI y, gmt::UnitI size, gmt::UnitI mass, gmt::UnitI damping, gmt::UnitI speed_x, gmt::UnitI speed_y, gmt::UnitI rotation, gmt::UnitI motor, bool fixed, bool tied,
               bool etherial)
    : Corpse(mass, damping, fixed, tied, etherial) {
    this->current_pos = gmt::VectorI(x, y);
    this->last_pos = gmt::VectorI(x - speed_x, y - speed_y);

    this->current_rotation = gmt::UnitI(0);
    this->last_rotation = rotation;

    this->size = size;
    this->motor = motor;
    this->propulsor = propulsor;

    this->bounds = gmt::BoundsI(this->get_pos_x() - this->get_size(), this->get_pos_y() - this->get_size(), this->get_pos_x() + this->get_size(), this->get_pos_y() + this->get_size());
}

Circle& Circle::operator=(const Circle& rhs) {
    Corpse::operator=(rhs);
    this->size = rhs.get_size();
    return *this;
}
// Circle::~Circle() {}

int Circle::get_class() const { return ID_CIRCLE; }
int Circle::id_class() { return ID_CIRCLE; }

void Circle::Step() {
    if (this->fixed) {
        this->last_pos = this->current_pos;
    } else {
        gmt::VectorI diff_pos = this->current_pos - this->last_pos;
        this->last_pos = this->current_pos;
        this->Drag(diff_pos);
    }

    if (this->tied) {
        this->last_rotation = std::fmod(this->current_rotation, gmt::UnitI(RO));
    } else {
        gmt::UnitI diff_rotation = this->current_rotation - this->last_rotation;
        this->last_rotation = this->current_rotation;
        this->Rotate(diff_rotation);
    }

    // Update bounds
    this->UpdateBounds();

    // Add the motor rotation even if the object is tied
    // if (!gmt::decimal_equals(motor, gmt::UnitI(0), gmt::UnitI(0.0001))) { this->current_rotation = this->current_rotation + motor; }
}
void Circle::UpdateBounds() {
    this->bounds = gmt::BoundsI(this->get_pos_x() - this->get_size(), this->get_pos_y() - this->get_size(), this->get_pos_x() + this->get_size(), this->get_pos_y() + this->get_size());
}
void Circle::Stop() { this->last_pos = this->current_pos; }
void Circle::Bloc() { this->last_rotation = this->current_rotation; }

void Circle::Move(const gmt::VectorI& move) { this->current_pos = move; }
void Circle::Drag(const gmt::VectorI& drag) { this->current_pos = this->current_pos + drag; }

void Circle::Turn(const gmt::UnitI& turn) { this->current_rotation = std::fmod(turn, gmt::UnitI(RO)); }
void Circle::Rotate(const gmt::UnitI& rotate) { this->current_rotation = std::fmod(this->current_rotation + rotate, gmt::UnitI(RO)); }

bool Circle::inBounds(const gmt::BoundsI& bounds) const { return gmt::BoundsI::BoundsInBounds(this->get_bounds(), bounds); }
bool Circle::Pointed(const gmt::VectorI& point) const { return (gmt::VectorI::Distance(this->get_pos(), point) <= this->size); }

gmt::UnitI Circle::get_size() const { return this->size; }
void Circle::set_size(const gmt::UnitI& size) { this->size = size; }

}  // namespace phy
#include "../../include/Constraints/Link.hpp"

namespace phy {

Link::Link(std::shared_ptr<phy::Corpse> corpse_a, std::shared_ptr<phy::Corpse> corpse_b, gmt::VectorI relative_pos_a, gmt::VectorI relative_pos_b, gmt::UnitI relative_angle_a,
           gmt::UnitI relative_angle_b, bool rotation_a, bool rotation_b, gmt::UnitI friction_a, gmt::UnitI friction_b, gmt::UnitI size, gmt::UnitI damping, gmt::UnitI max_size, gmt::UnitI min_size,
           bool breaking)
    : Constraint(corpse_a, corpse_b, relative_pos_a, relative_pos_b, relative_angle_a, relative_angle_b, rotation_a, rotation_b, friction_a, friction_b, breaking) {
    this->damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));

    gmt::VectorI position_a = corpse_a == nullptr ? relative_pos_a : corpse_a->get_pos() + relative_pos_a;
    gmt::VectorI position_b = corpse_b == nullptr ? relative_pos_b : corpse_b->get_pos() + relative_pos_b;

    this->size = (size < gmt::UnitI()) ? gmt::VectorI::Distance(position_a, position_b) : size;
    this->max_size = (max_size < gmt::UnitI()) ? this->size - max_size : max_size;
    this->min_size = (min_size < gmt::UnitI()) ? this->size + min_size : min_size;
}

Link& Link::operator=(const Link& rhs) {
    Constraint::operator=(rhs);
    this->damping = rhs.get_damping();
    this->size = rhs.get_size();
    this->max_size = rhs.get_size();
    this->min_size = rhs.get_size();
    return *this;
}

int Link::get_class() const { return ID_LINK; }
static int id_class() { return ID_LINK; }

void Link::Step() {
    gmt::VectorI diff = get_corpse_a()->get_pos() - get_corpse_b()->get_pos();
    gmt::UnitI current_size = std::sqrt(gmt::VectorI::Dot(diff, diff));

    gmt::UnitI percent = (current_size - size) / current_size;
    gmt::VectorI displacement = diff * percent * damping;

    if (breaking) {
        if (current_size > max_size || current_size < min_size) { this->broken = true; }
    }
    if (corpse_a->get_fixed() || corpse_b->get_fixed()) {
        if (!corpse_a->get_fixed()) {
            corpse_a->Drag(-displacement);
        } else if (!corpse_b->get_fixed()) {
            corpse_b->Drag(displacement);
        } else {
            /*
            corpse_a->Drag(-displacement / gmt::UnitI(2));
            corpse_b->Drag(displacement / gmt::UnitI(2));
            */
        }
    } else {
        gmt::UnitI mass = corpse_a->get_mass() + corpse_b->get_mass();
        corpse_a->Drag(-displacement * (corpse_b->get_mass() / mass));
        corpse_b->Drag(displacement * (corpse_a->get_mass() / mass));
    }

    if (rotation_a) {
        if (com::float_equals(friction_a, gmt::UnitI())) {}  // TODO Apply friction
    } else {
        // TODO Force from the relative rotation
    }

    if (rotation_b) {
        if (com::float_equals(friction_b, gmt::UnitI())) {}  // TODO Apply friction
    } else {
        // TODO Force from the relative rotation
    }
}

gmt::UnitI Link::get_size() const { return this->size; }
void Link::set_size(gmt::UnitI size) { this->size = size; }

gmt::UnitI Link::get_damping() const { return this->damping; }
void Link::set_damping(gmt::UnitI damping) { this->damping = damping; }

gmt::UnitI Link::get_max_size() const { return this->max_size; }
void Link::set_max_size(gmt::UnitI max_size) { this->max_size = max_size; }

gmt::UnitI Link::get_min_size() const { return this->min_size; }
void Link::set_min_size(gmt::UnitI min_size) { this->min_size = min_size; }

}  // namespace phy
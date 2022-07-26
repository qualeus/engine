#include "../../include/Constraints/Slider.hpp"

namespace phy {

Slider::Slider(std::shared_ptr<phy::Corpse> corpse_a, std::shared_ptr<phy::Corpse> corpse_b, gmt::VectorI relative_pos_a, gmt::VectorI relative_pos_b, gmt::UnitI relative_angle_a,
               gmt::UnitI relative_angle_b, bool rotation_a, bool rotation_b, gmt::UnitI friction_a, gmt::UnitI friction_b, gmt::UnitI damping, gmt::UnitI max_distance,
               std::vector<std::shared_ptr<phy::Corpse>> slider_corpses, std::vector<gmt::VectorI> slider_relative_pos, std::vector<bool> slider_rotations,
               std::vector<gmt::UnitI> slider_relative_angles, std::vector<gmt::UnitI> slider_frictions, bool breaking)
    : Constraint(corpse_a, corpse_b, relative_pos_a, relative_pos_b, relative_angle_a, relative_angle_b, rotation_a, rotation_b, friction_a, friction_b, breaking) {
    this->damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));
    this->max_distance = max_distance;
    this->slider_corpses = slider_corpses;
    this->slider_relative_pos = slider_relative_pos;
    this->slider_rotations = slider_rotations;
    this->slider_relative_angles = slider_relative_angles;
    this->slider_frictions = slider_frictions;
}
// Link& Link::operator=(const Link& rhs) {}

int Slider::get_class() const { return ID_SLIDER; }
static int id_class() { return ID_SLIDER; }

void Slider::Step() {
    /* Re align*/
    for (int i = 0; i < slider_corpses.size(); i++) {
        gmt::VectorI aligned = gmt::VectorI::SegmentProjection(get_slider_corpses()[i]->get_pos(), get_corpse_a()->get_pos(), get_corpse_b()->get_pos());
        get_slider_corpses()[i]->Move(aligned);
    }
    /* Limit to the interval */
    gmt::UnitI size = gmt::VectorI::Distance(get_corpse_a()->get_pos(), get_corpse_b()->get_pos());
    for (int i = 0; i < slider_corpses.size(); i++) {
        // Limit A
        gmt::VectorI diffA = get_slider_corpses()[i]->get_pos() - get_corpse_a()->get_pos();
        if (diffA.Magnitude() > size) {
            get_slider_corpses()[i]->Drag(-diffA + diffA.Normalize());
            get_slider_corpses()[i]->Stop();
            continue;
        }

        // Limit B
        gmt::VectorI diffB = get_slider_corpses()[i]->get_pos() - get_corpse_b()->get_pos();
        if (diffB.Magnitude() > size) {
            get_slider_corpses()[i]->Drag(-diffB + diffA.Normalize());
            get_slider_corpses()[i]->Stop();
            continue;
        }
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

Slider& Slider::operator=(const Slider& rhs) {
    Constraint::operator=(rhs);
    this->damping = rhs.get_damping();
    this->max_distance = rhs.get_max_distance();
    this->slider_corpses = rhs.get_slider_corpses();                  // TODO Manage vector copy objects
    this->slider_relative_pos = rhs.get_slider_relative_pos();        // TODO Manage vector copy objects
    this->slider_rotations = rhs.get_slider_rotations();              // TODO Manage vector copy objects
    this->slider_relative_angles = rhs.get_slider_relative_angles();  // TODO Manage vector copy objects
    this->slider_frictions = rhs.get_slider_frictions();              // TODO Manage vector copy objects
    return *this;
}

gmt::UnitI Slider::get_damping() const { return this->damping; }
void Slider::set_damping(gmt::UnitI damping) { this->damping = damping; }

gmt::UnitI Slider::get_max_distance() const { return this->max_distance; }
void Slider::set_max_distance(gmt::UnitI max_distance) { this->max_distance = max_distance; }

std::vector<std::shared_ptr<phy::Corpse>> Slider::get_slider_corpses() const { return this->slider_corpses; }
void Slider::set_slider_corpses(std::vector<std::shared_ptr<phy::Corpse>> slider_corpses) { this->slider_corpses = slider_corpses; }
int Slider::get_slider_corpses_size() const { return this->slider_corpses.size(); }
std::shared_ptr<phy::Corpse> Slider::get_slider_corpse(int index) const { return this->slider_corpses[index]; }
void Slider::set_slider_corpse(int index, std::shared_ptr<phy::Corpse> corpse) { this->slider_corpses[index] = corpse; }

std::vector<gmt::VectorI> Slider::get_slider_relative_pos() const { return this->slider_relative_pos; }
void Slider::set_slider_relative_pos(std::vector<gmt::VectorI> slider_relative_pos) { this->slider_relative_pos = slider_relative_pos; }

std::vector<bool> Slider::get_slider_rotations() const { return this->slider_rotations; }
void Slider::set_slider_rotations(std::vector<bool> slider_rotations) { this->slider_rotations = slider_rotations; }

std::vector<gmt::UnitI> Slider::get_slider_relative_angles() const { return this->slider_relative_angles; }
void Slider::set_slider_relative_angles(std::vector<gmt::UnitI> slider_relative_angles) { this->slider_relative_angles = slider_relative_angles; }

std::vector<gmt::UnitI> Slider::get_slider_frictions() const { return this->slider_frictions; }
void Slider::set_slider_frictions(std::vector<gmt::UnitI> slider_frictions) { this->slider_frictions = slider_frictions; }

void Slider::addCorpse(std::shared_ptr<phy::Corpse> corpse, gmt::VectorI relative_pos, bool rotation, gmt::UnitI relative_angle, gmt::UnitI friction) {
    this->slider_corpses.push_back(corpse);
    this->slider_relative_pos.push_back(relative_pos);
    this->slider_rotations.push_back(rotation);
    this->slider_relative_angles.push_back(relative_angle);
    this->slider_frictions.push_back(friction);
}

void Slider::removeCorpse(int index) {
    com::remove_unordered(index, slider_corpses);
    com::remove_unordered(index, slider_relative_pos);
    com::remove_unordered(index, slider_rotations);
    com::remove_unordered(index, slider_relative_angles);
    com::remove_unordered(index, slider_frictions);
}
};  // namespace phy
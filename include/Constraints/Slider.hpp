#ifndef Slider_HPP
#define Slider_HPP

#include "Config.hpp"
#include "Constraint.hpp"

namespace phy {

const static int ID_SLIDER = 4;

class Slider : public Constraint {
   private:
    gmt::UnitI damping;
    gmt::UnitI max_distance;

    std::vector<std::shared_ptr<phy::Corpse>> slider_corpses;
    std::vector<gmt::VectorI> slider_relative_pos;
    std::vector<bool> slider_rotations;
    std::vector<gmt::UnitI> slider_relative_angles;
    std::vector<gmt::UnitI> slider_frictions;

   public:
    Slider(std::shared_ptr<phy::Corpse> corpse_a = nullptr, std::shared_ptr<phy::Corpse> corpse_b = nullptr, gmt::VectorI relative_pos_a = gmt::VectorI(), gmt::VectorI relative_pos_b = gmt::VectorI(), gmt::UnitI relative_angle_a = gmt::UnitI(), gmt::UnitI relative_angle_b = gmt::UnitI(),
           bool rotation_a = true, bool rotation_b = true, gmt::UnitI friction_a = gmt::UnitI(), gmt::UnitI friction_b = gmt::UnitI(), gmt::UnitI damping = gmt::UnitI(1), gmt::UnitI max_distance = gmt::UnitI(0), std::vector<std::shared_ptr<phy::Corpse>> slider_corpses = {},
           std::vector<gmt::VectorI> slider_relative_pos = {}, std::vector<bool> slider_rotations = {}, std::vector<gmt::UnitI> slider_relative_angles = {}, std::vector<gmt::UnitI> slider_frictions = {}, bool breaking = false);
    Slider& operator=(const Slider& rhs);

    int get_class() const;
    static int id_class();

    void Step();

    gmt::UnitI get_damping() const;
    void set_damping(gmt::UnitI damping);

    gmt::UnitI get_max_distance() const;
    void set_max_distance(gmt::UnitI max_distance);

    std::vector<std::shared_ptr<phy::Corpse>> get_slider_corpses() const;
    void set_slider_corpses(std::vector<std::shared_ptr<phy::Corpse>> slider_corpses);
    int get_slider_corpses_size() const;
    std::shared_ptr<phy::Corpse> get_slider_corpse(int index) const;
    void set_slider_corpse(int index, std::shared_ptr<phy::Corpse> corpse);

    std::vector<gmt::VectorI> get_slider_relative_pos() const;
    void set_slider_relative_pos(std::vector<gmt::VectorI> slider_relative_pos);

    std::vector<bool> get_slider_rotations() const;
    void set_slider_rotations(std::vector<bool> slider_rotations);

    std::vector<gmt::UnitI> get_slider_relative_angles() const;
    void set_slider_relative_angles(std::vector<gmt::UnitI> slider_relative_angles);

    std::vector<gmt::UnitI> get_slider_frictions() const;
    void set_slider_frictions(std::vector<gmt::UnitI> slider_frictions);

    void addCorpse(std::shared_ptr<phy::Corpse> corpse, gmt::VectorI relative_pos = gmt::VectorI(), bool rotation = true, gmt::UnitI relative_angle = gmt::UnitI(), gmt::UnitI friction = gmt::UnitI());
    void removeCorpse(int index);
};
}  // namespace phy
#endif
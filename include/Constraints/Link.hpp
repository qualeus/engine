#ifndef Link_HPP
#define Link_HPP

#include "Config.hpp"
#include "Constraint.hpp"

namespace phy {

const static int ID_LINK = 2;

class Link : public Constraint {
   private:
    gmt::UnitI m_size;
    gmt::UnitI m_damping;
    gmt::UnitI m_max_size;
    gmt::UnitI m_min_size;

   public:
    Link(std::shared_ptr<phy::Corpse> corpse_a = nullptr,
         std::shared_ptr<phy::Corpse> corpse_b = nullptr,
         gmt::VectorI relative_pos_a = gmt::VectorI(),
         gmt::VectorI relative_pos_b = gmt::VectorI(),
         gmt::UnitI relative_angle_a = gmt::UnitI(),
         gmt::UnitI relative_angle_b = gmt::UnitI(),
         bool rotation_a = true,
         bool rotation_b = true,
         gmt::UnitI friction_a = gmt::UnitI(),
         gmt::UnitI friction_b = gmt::UnitI(),
         gmt::UnitI size = gmt::UnitI(-1),
         gmt::UnitI damping = gmt::UnitI(1),
         gmt::UnitI max_size = gmt::UnitI(-1),
         gmt::UnitI min_size = gmt::UnitI(-1),
         bool breaking = false);

    Link& operator=(const Link& rhs);

    int get_class() const;
    static int id_class();

    void step();

    gmt::UnitI get_size() const;
    void set_size(gmt::UnitI size);

    gmt::UnitI get_damping() const;
    void set_damping(gmt::UnitI damping);

    gmt::UnitI get_max_size() const;
    void set_max_size(gmt::UnitI max_size);

    gmt::UnitI get_min_size() const;
    void set_min_size(gmt::UnitI min_size);
};
}  // namespace phy
#endif
#ifndef Link_HPP
#define Link_HPP

#include "Config.hpp"
#include "Constraint.hpp"

namespace phy {

class Link : public Constraint {
   private:
    gmt::VectorI m_pos_a;
    gmt::VectorI m_pos_b;

    gmt::UnitI m_size;
    gmt::UnitI m_damping;

   public:
    Link();
    Link(com::sptr<phy::Corpse> corpse_a = nullptr,
         com::sptr<phy::Corpse> corpse_b = nullptr,
         gmt::VectorI pos_a              = gmt::VectorI(),
         gmt::VectorI pos_b              = gmt::VectorI(),
         gmt::UnitI damping              = gmt::UnitI());

    Link& operator=(const Link& rhs);

    gmt::UnitI get_size() const;
    void set_size(gmt::UnitI size);

    gmt::UnitI get_damping() const;
    void set_damping(gmt::UnitI damping);

    void balance();
};
}  // namespace phy
#endif
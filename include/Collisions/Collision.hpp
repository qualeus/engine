#ifndef Collision_HPP
#define Collision_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Geometry.hpp"
#include "Config.hpp"

namespace phy {

class Collision {
   private:
    com::sptr<phy::Corpse> m_corpse_a;
    com::sptr<phy::Corpse> m_corpse_b;

   public:
    Collision();
    Collision(com::sptr<phy::Corpse> corpse_a = nullptr, com::sptr<phy::Corpse> corpse_b = nullptr);

    com::sptr<phy::Corpse> get_corpse_a() const;
    void set_corpse_a(com::sptr<phy::Corpse> corpse_a);

    com::sptr<phy::Corpse> get_corpse_b() const;
    void set_corpse_b(com::sptr<phy::Corpse> corpse_b);
};

}  // namespace phy
#endif
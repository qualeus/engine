#ifndef Contraint_HPP
#define Contraint_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Geometry.hpp"
#include "Config.hpp"

namespace phy {

class Constraint {
   protected:
    com::sptr<phy::Corpse> m_corpse_a;
    com::sptr<phy::Corpse> m_corpse_b;

   public:
    explicit Constraint(com::sptr<phy::Corpse> corpse_a, com::sptr<phy::Corpse> corpse_b);

    inline bool operator==(const Constraint* other);
    Constraint& operator=(const Constraint& rhs);

    com::sptr<phy::Corpse> get_corpse_a() const;
    void set_corpse_a(com::sptr<phy::Corpse> corpse_a);

    com::sptr<phy::Corpse> get_corpse_b() const;
    void set_corpse_b(com::sptr<phy::Corpse> corpse_b);

    virtual void balance() = 0;
};
}  // namespace phy

#endif
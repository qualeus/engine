#ifndef Integrator_HPP
#define Integrator_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Corpse.hpp"

namespace gmt {

class Integrator {
   public:
    Integrator();
    virtual void integrate(com::sptr<phy::Corpse> corpse, double dt) = 0;
};

}  // namespace gmt

#endif
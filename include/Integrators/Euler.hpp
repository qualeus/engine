#ifndef Euler_HPP
#define Euler_HPP

#include "Integrator.hpp"

namespace gmt {

class Euler : public Integrator {
   public:
    Euler();
    void integrate(com::sptr<phy::Corpse> corpse, double dt);
};

}  // namespace gmt

#endif
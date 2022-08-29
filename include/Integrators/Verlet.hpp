#ifndef Verlet_HPP
#define Verlet_HPP

#include "Integrator.hpp"

namespace gmt {

class Verlet : public Integrator {
   public:
    Verlet();
    void integrate(com::sptr<phy::Corpse> corpse, double dt);
};

}  // namespace gmt

#endif
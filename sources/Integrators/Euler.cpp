#include "../../include/Integrators/Euler.hpp"

namespace gmt {

Euler::Euler() { }

void Euler::integrate(com::sptr<phy::Corpse> corpse, double dt) {

    gmt::VectorI acc = corpse->get_acc();
    gmt::VectorI vel = corpse->get_vel();
    gmt::VectorI pos = corpse->get_pos();

    corpse->set_vel(vel + acc * dt);
    corpse->set_pos(pos + vel * dt);
    corpse->set_acc(gmt::VectorI());  // reset force accumulator

    gmt::UnitI tor = corpse->get_tor();
    gmt::UnitI spi = corpse->get_spi();
    gmt::UnitI rot = corpse->get_rot();

    corpse->set_spi(spi + tor * dt);
    corpse->set_rot(rot + spi * dt);
    corpse->set_tor(gmt::UnitI());  // reset torque accumulator
}

}  // namespace gmt
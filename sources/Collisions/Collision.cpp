#include "../../include/Collisions/Collision.hpp"

namespace phy {

Collision::Collision() {
    m_corpse_a = nullptr;
    m_corpse_b = nullptr;
}

Collision::Collision(com::sptr<phy::Corpse> corpse_a, com::sptr<phy::Corpse> corpse_b) {
    m_corpse_a = corpse_a;
    m_corpse_b = corpse_b;
}

com::sptr<phy::Corpse> Collision::get_corpse_a() const {
    return m_corpse_a;
}

void Collision::set_corpse_a(com::sptr<phy::Corpse> corpse_a) {
    m_corpse_a = corpse_a;
}

com::sptr<phy::Corpse> Collision::get_corpse_b() const {
    return m_corpse_b;
}

void Collision::set_corpse_b(com::sptr<phy::Corpse> corpse_b) {
    m_corpse_b = corpse_b;
}

}  // namespace phy
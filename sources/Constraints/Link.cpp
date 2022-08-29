#include "../../include/Constraints/Link.hpp"

namespace phy {

Link::Link() : Constraint(nullptr, nullptr) {

    m_pos_a   = gmt::VectorI();
    m_pos_b   = gmt::VectorI();
    m_damping = gmt::UnitI();
    m_size    = gmt::UnitI();
}

Link::Link(com::sptr<phy::Corpse> corpse_a, com::sptr<phy::Corpse> corpse_b, gmt::VectorI pos_a, gmt::VectorI pos_b, gmt::UnitI damping) : Constraint(corpse_a, corpse_b) {

    m_pos_a   = pos_a;
    m_pos_b   = pos_b;
    m_damping = damping;
    m_size    = 0;  // TODO compute
}

Link& Link::operator=(const Link& rhs) {
    Constraint::operator=(rhs);
    m_damping = rhs.get_damping();
    m_size    = rhs.get_size();
    return *this;
}

gmt::UnitI Link::get_size() const {
    return m_size;
}

void Link::set_size(gmt::UnitI size) {
    m_size = size;
}

gmt::UnitI Link::get_damping() const {
    return m_damping;
}

void Link::set_damping(gmt::UnitI damping) {
    m_damping = damping;
}

void Link::balance() { }

}  // namespace phy
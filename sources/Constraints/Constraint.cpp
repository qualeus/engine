#include "../../include/Constraints/Constraint.hpp"

namespace phy {

Constraint::Constraint(com::sptr<phy::Corpse> corpse_a, com::sptr<phy::Corpse> corpse_b) {
    static int global_constraint_id = 0;

    m_corpse_a = corpse_a;
    m_corpse_b = corpse_b;
}

Constraint& Constraint::operator=(const Constraint& rhs) {

    m_corpse_a = rhs.get_corpse_a();
    m_corpse_b = rhs.get_corpse_b();

    return *this;
}

inline bool Constraint::operator==(const Constraint* other) {
    return false;  // TODO
}

com::sptr<phy::Corpse> Constraint::get_corpse_a() const {
    return m_corpse_a;
}

void Constraint::set_corpse_a(com::sptr<phy::Corpse> corpse_a) {
    m_corpse_a = corpse_a;
}

com::sptr<phy::Corpse> Constraint::get_corpse_b() const {
    return m_corpse_b;
}

void Constraint::set_corpse_b(com::sptr<phy::Corpse> corpse_b) {
    m_corpse_b = corpse_b;
}

}  // namespace phy
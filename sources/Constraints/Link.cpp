#include "../../include/Constraints/Link.hpp"

namespace phy {

Link::Link(std::shared_ptr<phy::Corpse> corpse_a,
           std::shared_ptr<phy::Corpse> corpse_b,
           gmt::VectorI relative_pos_a,
           gmt::VectorI relative_pos_b,
           gmt::UnitI relative_angle_a,
           gmt::UnitI relative_angle_b,
           bool rotation_a,
           bool rotation_b,
           gmt::UnitI friction_a,
           gmt::UnitI friction_b,
           gmt::UnitI size,
           gmt::UnitI damping,
           gmt::UnitI max_size,
           gmt::UnitI min_size,
           bool breaking)

    : Constraint(corpse_a, corpse_b, relative_pos_a, relative_pos_b, relative_angle_a, relative_angle_b, rotation_a, rotation_b, friction_a, friction_b, breaking) {
    m_damping = com::minmax_filter(damping, gmt::UnitI(MIN_DAMPING), gmt::UnitI(MAX_DAMPING));

    gmt::VectorI position_a = corpse_a == nullptr ? relative_pos_a : corpse_a->get_pos() + relative_pos_a;
    gmt::VectorI position_b = corpse_b == nullptr ? relative_pos_b : corpse_b->get_pos() + relative_pos_b;

    m_size = (size < gmt::UnitI()) ? gmt::VectorI::distance(position_a, position_b) : size;
    m_max_size = (max_size < gmt::UnitI()) ? m_size - max_size : max_size;
    m_min_size = (min_size < gmt::UnitI()) ? m_size + min_size : min_size;
}

Link& Link::operator=(const Link& rhs) {
    Constraint::operator=(rhs);
    m_damping = rhs.get_damping();
    m_size = rhs.get_size();
    m_max_size = rhs.get_size();
    m_min_size = rhs.get_size();
    return *this;
}

int Link::get_class() const {
    return ID_LINK;
}
static int id_class() {
    return ID_LINK;
}

void Link::step() {
    gmt::VectorI diff = get_corpse_a()->get_pos() - get_corpse_b()->get_pos();
    gmt::UnitI current_size = std::sqrt(gmt::VectorI::dot(diff, diff));

    gmt::UnitI percent = (current_size - m_size) / current_size;
    gmt::VectorI displacement = diff * percent * m_damping;

    if (m_breaking) {
        if (current_size > m_max_size || current_size < m_min_size) { m_broken = true; }
    }

    if (m_corpse_a->get_fixed() || m_corpse_b->get_fixed()) {
        if (!m_corpse_a->get_fixed()) {
            m_corpse_a->drag(-displacement);
        } else if (!m_corpse_b->get_fixed()) {
            m_corpse_b->drag(displacement);
        } else {
            /*
            m_corpse_a->drag(-displacement / gmt::UnitI(2));
            m_corpse_b->drag(displacement / gmt::UnitI(2));
            */
        }
    } else {
        gmt::UnitI mass = m_corpse_a->get_mass() + m_corpse_b->get_mass();
        m_corpse_a->drag(-displacement * (m_corpse_b->get_mass() / mass));
        m_corpse_b->drag(displacement * (m_corpse_a->get_mass() / mass));
    }

    if (m_rotation_a) {
        if (com::float_equals(m_friction_a, gmt::UnitI())) { }  // TODO Apply friction
    } else {
        // TODO Force from the relative rotation
    }

    if (m_rotation_b) {
        if (com::float_equals(m_friction_b, gmt::UnitI())) { }  // TODO Apply friction
    } else {
        // TODO Force from the relative rotation
    }
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

gmt::UnitI Link::get_max_size() const {
    return m_max_size;
}

void Link::set_max_size(gmt::UnitI max_size) {
    m_max_size = max_size;
}

gmt::UnitI Link::get_min_size() const {
    return m_min_size;
}

void Link::set_min_size(gmt::UnitI min_size) {
    m_min_size = min_size;
}

}  // namespace phy
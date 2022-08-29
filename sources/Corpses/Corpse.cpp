#include "../../include/Corpses/Corpse.hpp"
namespace phy {

Corpse::Corpse() {
    static int global_corpse_id = 0;

    m_id = global_corpse_id++;

    m_fixed    = false;
    m_tied     = false;
    m_etherial = false;

    m_pos = gmt::VectorI();
    m_vel = gmt::VectorI();
    m_acc = gmt::VectorI();

    m_rot = gmt::UnitI();
    m_spi = gmt::UnitI();
    m_tor = gmt::UnitI();

    m_shapes = {};
}

Corpse& Corpse::operator=(const Corpse& rhs) {
    m_id = rhs.get_id();

    m_fixed    = rhs.get_fixed();
    m_tied     = rhs.get_tied();
    m_etherial = rhs.get_etherial();

    m_pos = rhs.get_pos();
    m_vel = rhs.get_vel();
    m_acc = rhs.get_acc();

    m_rot = rhs.get_rot();
    m_spi = rhs.get_spi();
    m_tor = rhs.get_tor();

    // fill with other shapes copy
    m_shapes = rhs.get_copy_shapes();

    return *this;
}

// Identifier getter
int Corpse::get_id() const {
    return m_id;
}

// State getters
bool Corpse::get_fixed() const {
    return m_fixed;
}
bool Corpse::get_tied() const {
    return m_tied;
}
bool Corpse::get_etherial() const {
    return m_etherial;
}

// State setters
void Corpse::set_fixed(bool fixed) {
    m_fixed = fixed;
}
void Corpse::set_etherial(bool etherial) {
    m_etherial = etherial;
}
void Corpse::set_tied(bool tied) {
    m_tied = tied;
}

// Position getters
gmt::VectorI Corpse::get_pos() const {
    return m_pos;
}
gmt::VectorI Corpse::get_vel() const {
    return m_vel;
}
gmt::VectorI Corpse::get_acc() const {
    return m_acc;
}

// Position setters
void Corpse::set_pos(gmt::VectorI pos) {
    m_pos = pos;
}
void Corpse::set_vel(gmt::VectorI vel) {
    m_vel = vel;
}
void Corpse::set_acc(gmt::VectorI acc) {
    m_acc = acc;
}

// Rotation setters
gmt::UnitI Corpse::get_rot() const {
    return m_rot;
}
gmt::UnitI Corpse::get_spi() const {
    return m_spi;
}
gmt::UnitI Corpse::get_tor() const {
    return m_tor;
}

// Rotation getters
void Corpse::set_rot(gmt::UnitI rot) {
    m_rot = rot;
}
void Corpse::set_spi(gmt::UnitI spi) {
    m_spi = spi;
}
void Corpse::set_tor(gmt::UnitI tor) {
    m_tor = tor;
}

gmt::UnitI Corpse::get_mass() const {
    return m_mass;
}
gmt::UnitI Corpse::get_moment() const {
    return m_moment;
}

void Corpse::add_shape(com::sptr<Shape> shape) {
    m_shapes.push_back(shape);
    calibrate();  // update mass and centroid
}

void Corpse::remove_shape(int i) {
    com::remove_unordered(i, m_shapes);
    calibrate();  // update mass and centroid
}

com::sptr<Shape> Corpse::get_shape(int i) const {
    return m_shapes[i];
}

com::vec<com::sptr<Shape>> Corpse::get_shapes() const {
    return m_shapes;
}

void Corpse::set_shapes(com::vec<com::sptr<Shape>> shapes) {
    m_shapes = shapes;
}

int Corpse::get_shapes_size() const {
    return m_shapes.size();
}

void Corpse::calibrate() {
    m_mass = gmt::UnitI();
    m_pos  = gmt::VectorI();

    // Update mass and local centroid
    for (int i = 0; i < m_shapes.size(); ++i) {
        m_mass += m_shapes[i]->get_mass();                               // accumulate shapes mass
        m_pos += m_shapes[i]->get_centroid() * m_shapes[i]->get_mass();  // weighted contributions
    }

    m_pos /= m_mass;  // normalize weighted contributions for centroid

    m_moment = gmt::UnitI();

    // https://en.wikipedia.org/wiki/Parallel_axis_theorem
    for (int i = 0; i < m_shapes.size(); ++i) {
        // TODO: implement moment of inertia (I) accumumlation from the shapes
    }
}

void Corpse::apply_force(gmt::VectorI force, gmt::VectorI at) {
    m_acc += force;
    m_tor += gmt::VectorI::cross(at - m_pos, force);
}

com::vec<com::sptr<Shape>> Corpse::get_copy_shapes() const {

    com::vec<com::sptr<Shape>> copy_shapes = {};

    for (int i = 0; i < m_shapes.size(); ++i) {
        if (Circle* lcircle = dynamic_cast<Circle*>(m_shapes[i].get())) {

            Circle shape_copy = *lcircle;
            copy_shapes.push_back(com::make_sptr<Circle>(shape_copy));

        } else if (Polygon* lpolygon = dynamic_cast<Polygon*>(m_shapes[i].get())) {

            Polygon shape_copy = *lpolygon;
            copy_shapes.push_back(com::make_sptr<Polygon>(shape_copy));

        } else if (Edge* ledge = dynamic_cast<Edge*>(m_shapes[i].get())) {

            phy::Edge shape_copy = *ledge;
            copy_shapes.push_back(com::make_sptr<Edge>(shape_copy));
        }
    }

    return copy_shapes;
}

gmt::VectorI Corpse::local_to_global(gmt::VectorI local) const {

    // 2D rotation matrix
    // [ cos(a), -sin(a) ]
    // [ sin(a),  cos(a) ]
    gmt::MatrixI rotation = {std::cos(m_rot), -std::sin(m_rot), std::sin(m_rot), std::cos(m_rot)};

    gmt::VectorI rotated_local = rotation * local;

    return rotated_local + m_pos;
}

gmt::VectorI Corpse::global_to_local(gmt::VectorI global) const {

    gmt::VectorI local = global - m_pos;

    // 2D inv rotation matrix
    // [ cos(a), sin(a) ]
    // [ -sin(a),  cos(a) ]
    gmt::MatrixI inv_rotation = {std::cos(m_rot), std::sin(m_rot), -std::sin(m_rot), std::cos(m_rot)};

    gmt::VectorI inv_rotated_local = inv_rotation * local;

    return inv_rotated_local;
}

bool Corpse::pointed(gmt::VectorI pos) const {

    gmt::VectorI local_pos = global_to_local(pos);
    for (int i = 0; i < m_shapes.size(); i++) {
        if (m_shapes[i]->pointed(local_pos)) return true;
    }

    return false;
}

}  // namespace phy
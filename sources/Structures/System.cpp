#include "../../include/Structures/System.hpp"

namespace phy {

System::System(bool gravity, gmt::UnitI force_x, gmt::UnitI force_y, gmt::UnitI limit_x, gmt::UnitI limit_y, int quadtree_max_count, int quadtree_max_depth)
    : m_quadtree(gmt::BoundsI(-limit_x / gmt::UnitI(2), -limit_y / gmt::UnitI(2), limit_x / gmt::UnitI(2), limit_y / gmt::UnitI(2)), quadtree_max_count, quadtree_max_depth) {
    m_gravity = gravity;
    m_force_x = force_x;
    m_force_y = force_y;

    m_corpses = {};
    m_quad_pairs = {};
    m_collisions = {};
    m_references = {};

    gmt::UnitI mid_limx = limit_x / gmt::UnitI(2);
    gmt::UnitI mid_limy = limit_y / gmt::UnitI(2);

    m_limits = gmt::BoundsI(-mid_limx, -mid_limy, mid_limx, mid_limy);
    m_enable_limits = true;
}

System::System(const System& other) : m_quadtree() {
    operator=(other);
}

System& System::operator=(const System& rhs) {
    m_force_x = rhs.get_force_x();
    m_force_y = rhs.get_force_y();
    m_gravity = rhs.get_gravity();
    m_ls = rhs.get_ls();
    m_g = rhs.get_g();

    m_dt = rhs.get_dt();
    m_collision_accuracy = rhs.get_collision_accuracy();
    m_constraint_accuracy = rhs.get_constraint_accuracy();

    m_limits = rhs.get_limits();

    m_corpses = {};
    m_constraints = {};
    m_quad_pairs = {};
    m_collisions = {};

    m_quadtree = rhs.m_quadtree;
    m_enable_limits = rhs.m_enable_limits;

    for (int i = 0; i < rhs.get_corpses_size(); i++) {
        // Populate the corpses array
        std::shared_ptr<phy::Corpse> temp_corpse = rhs.get_corpse(i);
        if (phy::Circle* circle = dynamic_cast<phy::Circle*>(temp_corpse.get())) {
            Circle circle_copy;
            circle_copy = *circle;
            add_corpse(std::make_shared<phy::Circle>(circle_copy));
        } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(temp_corpse.get())) {
            Polygon polygon_copy;
            polygon_copy = *polygon;
            add_corpse(std::make_shared<phy::Polygon>(polygon_copy));
        }
    }

    for (int i = 0; i < rhs.get_constraints_size(); i++) {
        // Populate the constraints array
        std::shared_ptr<phy::Constraint> temp_constraint = rhs.get_constraint(i);
        if (phy::Link* link = dynamic_cast<phy::Link*>(temp_constraint.get())) {
            Link link_copy;
            link_copy = *link;

            link_copy.set_corpse_a(get_corpse_by_id(link_copy.get_corpse_a()->get_id()));
            link_copy.set_corpse_b(get_corpse_by_id(link_copy.get_corpse_b()->get_id()));

            m_constraints.push_back(std::make_shared<phy::Link>(link_copy));
        }
    }

    return *this;
}

System::~System() { }

void System::step() {
    bmk::Record("Step");

    m_collisions = {};
    m_quad_pairs = {};

    // Update Positions
    {
        bmk::Record("Corpses");
        corpses_step();
    }
    {
        bmk::Record("Forces");
        forces_step();
    }
    {
        bmk::Record("Constraints");

        for (int i = 0; i < m_constraint_accuracy; i++) {
            // std::string label = "Constraint " + i;
            // bmk::Record(label.c_str());
            constraints_step();
        }
    }

    // Check the Limits
    if (m_enable_limits) {
        bmk::Record("Limits");
        check_limits();
    }

    // Update Forces
    // Update Velocities
    // Apply Boundaries conditions
    {
        bmk::Record("QuadTree");
        step_quad_tree();
    }

    {
        bmk::Record("Collisions");

        for (int i = 0; i < m_collision_accuracy; i++) {
            // std::string label = "Collision " + i;
            // bmk::Record("Collision " + com::to_string(i));
            quad_pairs_step();
        }
    }
    {
        bmk::Record("Pairs");
        pairs_step();
    }

    // Move Global Time
    {
        bmk::Record("Time");
        update_time();
    }
}
void System::update_time() {
    m_t += m_dt;
}

void System::check_limits() {
    for (int i = 0; i < m_corpses.size(); i++) {
        if (gmt::BoundsI::bounds_out_bounds(get_corpse(i)->get_bounds(), get_limits())) { remove(i); }
    }
}

void System::corpses_step() {
    for (int i = 0; i < m_corpses.size(); i++) { get_corpse(i)->step(); }
}

void System::forces_step() {
    for (int i = 0; i < m_corpses.size(); i++) {
        if (!get_corpse(i)->get_fixed()) { get_corpse(i)->drag(gmt::VectorI(m_force_x, m_force_y) * m_dt * m_dt); }
    }
}

void System::constraints_step() {
    for (int i = 0; i < m_constraints.size(); i++) {
        get_constraint(i)->step();
        if (get_constraint(i)->get_broken()) { com::remove_unordered(i, m_constraints); }
    }
}

void System::corpse_update_bounds(int i) {
    if (phy::Circle* circle = dynamic_cast<phy::Circle*>(get_corpse(i).get())) {
        circle->update_bounds();
    } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(get_corpse(i).get())) {
        polygon->update_bounds();
    }
}

void System::corpse_stop(int i) {
    if (phy::Circle* circle = dynamic_cast<phy::Circle*>(get_corpse(i).get())) {
        circle->stop();
    } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(get_corpse(i).get())) {
        polygon->stop();
    }
}

void System::pairs_step() {
    /*
    // Old broad phase
    for (int i = 0; i < get_corpses_size(); i++) {
        for (int j = i + 1; j < get_corpses_size(); j++) {
            std::vector<gmt::CollisionI> resolved = gmt::CollisionI::Resolve(get_corpse(i), get_corpse(j));
            for (int k = 0; k < resolved.size(); k++) { m_collisions.push_back(resolved[k]); }
        }
    }
    */
    if (m_gravity) {
        for (int i = 0; i < get_corpses_size(); i++) {
            for (int j = i + 1; j < get_corpses_size(); j++) { gravity(get_corpse(i), get_corpse(j)); }
        }
    }
}

void System::quad_pairs_step() {
    for (int i = 0; i < get_quad_pairs_depth(); i++) {
        int k = 0;
        for (int j = 0; j < m_quad_pairs[i].second.size(); j++) {
            int node_pairs_size = m_quad_pairs[i].second[j];
            thread_pairs_step(i, k, k + node_pairs_size);
            k += node_pairs_size;
        }
    }
}

void System::thread_pairs_step(int depth, int begin, int end) {
    for (int i = begin; i < end; i++) {
        std::vector<gmt::CollisionI> resolved = gmt::CollisionI::resolve(m_quad_pairs[depth].first[i].first, m_quad_pairs[depth].first[i].second);
        for (int j = 0; j < resolved.size(); j++) { m_collisions.push_back(resolved[j]); }
    }
}

void System::clear() {
    m_corpses = {};
    m_constraints = {};
    m_references = {};
}

void System::remove(int i) {
    std::shared_ptr<Corpse> ptr = com::remove_unordered_return(i, m_corpses);
    com::remove_lambda(m_constraints, [ptr](std::shared_ptr<phy::Constraint> constraint) { return constraint->get_corpse_a() == ptr || constraint->get_corpse_b() == ptr; });
    m_references.erase(ptr->get_id());
}

void System::gravity(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b) {
    if (a->get_fixed() && b->get_fixed()) { return; }  // Both Fixed

    gmt::UnitI dist = gmt::VectorI::distance(a->get_pos(), b->get_pos());
    if (dist > gmt::UnitI(MAX_GRAVITY_DISTANCE)) { return; }  // Avoid strange behaviour with big numbers

    // Possible optimisation: Remove the multiplication and division by the mass and
    // just multiply the force by the other body mass when applying it

    gmt::UnitI force = m_g * a->get_mass() * b->get_mass() / (dist * dist);  // G * (ma * mb)/(r^2)
    if (force > m_ls) { force = m_ls; }                                      // Limit with the Light Speed

    gmt::VectorI diff = gmt::VectorI(b->get_pos_x() - a->get_pos_x(), b->get_pos_y() - a->get_pos_y()) / dist;
    gmt::VectorI acceleration_a = diff * force / a->get_mass();
    gmt::VectorI acceleration_b = -diff * force / b->get_mass();

    if (!a->get_fixed()) { a->drag(acceleration_a * m_dt * m_dt); }
    if (!b->get_fixed()) { b->drag(acceleration_b * m_dt * m_dt); }
}

void System::step_quad_tree() {
    m_quadtree.clear();

    for (int i = 0; i < m_corpses.size(); i++) {
        if (!get_corpse(i)->get_etherial()) { m_quadtree.add_corpse(get_corpse(i)); }
    }

    m_quad_pairs = m_quadtree.compute_pairs();
    // m_quadtree.Update();
}

gmt::QuadTree* System::get_quadtree() {
    return &m_quadtree;
}

gmt::UnitI System::get_dt() const {
    return m_dt;
}
void System::set_dt(gmt::UnitI dt) {
    // We compute the change in time
    gmt::UnitI dt_diff = dt - m_dt;

    // We need to avoid a dt to close to 0 because
    // it mess up with the corpses velocities.
    // It's better to just pass the area around 0.
    if (!com::float_equals(dt, gmt::UnitI(0), dt_diff / gmt::UnitI(10))) {
        dt = dt + dt_diff;
        dt_diff = dt_diff * gmt::UnitI(2);
    }

    gmt::UnitI dt_frac = dt / m_dt;

    for (int i = 0; i < m_corpses.size(); i++) {
        // Update corpses velocities an rotations
        get_corpse(i)->set_last_pos(get_corpse(i)->get_pos() - get_corpse(i)->get_diff_pos() * dt_frac);
        get_corpse(i)->set_last_rotation(get_corpse(i)->get_rotation() - get_corpse(i)->get_diff_rotation() * dt_frac);
    }

    m_dt = dt;
}
void System::invert_dt() {
    set_dt(-m_dt);
}

double System::get_t() const {
    return m_t;
}
void System::set_t(double t) {
    m_t = t;
}

gmt::UnitI System::get_force_x() const {
    return m_force_x;
}
void System::set_force_x(gmt::UnitI force_x) {
    m_force_x = force_x;
}

gmt::UnitI System::get_force_y() const {
    return m_force_y;
}
void System::set_force_y(gmt::UnitI force_y) {
    m_force_y = force_y;
}

bool System::get_gravity() const {
    return m_gravity;
}
void System::set_gravity(bool gravity) {
    m_gravity = gravity;
}

gmt::UnitI System::get_ls() const {
    return m_ls;
}
void System::set_ls(gmt::UnitI ls) {
    m_ls = ls;
}

gmt::UnitI System::get_g() const {
    return m_g;
}
void System::set_g(gmt::UnitI f) {
    m_g = f;
}

int System::get_collision_accuracy() const {
    return m_collision_accuracy;
}
void System::set_collision_accuracy(int collision_accuracy) {
    m_collision_accuracy = collision_accuracy;
}

int System::get_constraint_accuracy() const {
    return m_constraint_accuracy;
}
void System::set_constraint_accuracy(int constraint_accuracy) {
    m_constraint_accuracy = constraint_accuracy;
}

int System::get_corpses_size() const {
    return m_corpses.size();
}
int System::get_constraints_size() const {
    return m_constraints.size();
}

int System::get_pairs_size() const {
    return (get_corpses_size() * (get_corpses_size() - 1)) / 2;  // [n (n - 1)] / 2;
}

int System::get_quad_pairs_depth() const {
    return m_quad_pairs.size();
}

int System::get_quad_pairs_size() const {
    int size = 0;
    for (int i = 0; i < get_quad_pairs_depth(); i++) { size += m_quad_pairs[i].first.size(); }
    return size;
}

int System::get_quad_pairs_size(int depth) const {
    if (m_quad_pairs.size() < depth + 1) { return 0; }
    return m_quad_pairs[depth].first.size();
}

std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>> System::get_quad_pair(int index, int depth) const {
    return m_quad_pairs[depth].first[index];
}

void System::add_corpse(Polygon polygon) {
    add_corpse(std::make_shared<Polygon>(polygon));
}
void System::add_corpse(Circle circle) {
    add_corpse(std::make_shared<Circle>(circle));
}

void System::add_constraint(Link link) {
    add_constraint(std::make_shared<Link>(link));
}

void System::add_corpse(std::shared_ptr<Corpse> corpse) {
    m_corpses.emplace_back(corpse);
    m_references[corpse->get_id()] = corpse;
}

void System::add_constraint(std::shared_ptr<Constraint> constraint) {
    m_constraints.emplace_back(std::move(constraint));
}

gmt::BoundsI System::get_limits() const {
    return m_limits;
}
void System::set_limits(gmt::BoundsI limits) {
    m_limits = limits;
    m_quadtree.limits = limits;
}

std::vector<std::shared_ptr<Corpse>> System::get_corpses() const {
    return m_corpses;
}
std::vector<std::shared_ptr<Constraint>> System::get_constraints() const {
    return m_constraints;
}

std::shared_ptr<Corpse> System::get_corpse(int index) const {
    return m_corpses[index];
}
std::shared_ptr<Corpse> System::get_corpse_by_id(int index) const {
    auto found = m_references.find(index);
    if (found != m_references.end()) {
        return found->second;
    } else {
        return nullptr;
    }
}
std::shared_ptr<Constraint> System::get_constraint(int index) const {
    return m_constraints[index];
}

gmt::CollisionI System::get_collision(int index) const {
    return m_collisions[index];
}
std::vector<gmt::CollisionI> System::get_collisions() const {
    return m_collisions;
}
int System::get_collisions_size() const {
    return m_collisions.size();
}

bool System::get_enable_limits() const {
    return m_enable_limits;
}
void System::set_enable_limits(bool enable_limits) {
    m_enable_limits = enable_limits;
}

}  // namespace phy
#include "../../include/Structures/System.hpp"

namespace phy {

System::System(bool gravity, gmt::UnitI force_x, gmt::UnitI force_y, gmt::UnitI limit_x, gmt::UnitI limit_y, int quadtree_max_count, int quadtree_max_depth)
    : quadtree(gmt::BoundsI(-limit_x / gmt::UnitI(2), -limit_y / gmt::UnitI(2), limit_x / gmt::UnitI(2), limit_y / gmt::UnitI(2)), quadtree_max_count, quadtree_max_depth) {
    this->gravity = gravity;
    this->force_x = force_x;
    this->force_y = force_y;

    this->corpses = {};
    this->quad_pairs = {};
    this->collisions = {};
    this->references = {};

    gmt::UnitI mid_limx = limit_x / gmt::UnitI(2);
    gmt::UnitI mid_limy = limit_y / gmt::UnitI(2);

    this->limits = gmt::BoundsI(-mid_limx, -mid_limy, mid_limx, mid_limy);
    this->enable_limits = true;
}

System::System(const System& other) : quadtree() { operator=(other); }

System& System::operator=(const System& rhs) {
    this->force_x = rhs.get_force_x();
    this->force_y = rhs.get_force_y();
    this->gravity = rhs.get_gravity();
    this->LS = rhs.get_LS();
    this->G = rhs.get_G();

    this->dt = rhs.get_dt();
    this->collision_accuracy = rhs.get_collision_accuracy();
    this->constraint_accuracy = rhs.get_constraint_accuracy();

    this->limits = rhs.get_limits();

    this->corpses = {};
    this->constraints = {};
    this->quad_pairs = {};
    this->collisions = {};

    this->quadtree = rhs.quadtree;
    this->enable_limits = rhs.enable_limits;

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

            link_copy.set_corpse_a(this->get_corpse_by_id(link_copy.get_corpse_a()->get_id()));
            link_copy.set_corpse_b(this->get_corpse_by_id(link_copy.get_corpse_b()->get_id()));

            this->constraints.push_back(std::make_shared<phy::Link>(link_copy));
        } else if (phy::Spring* spring = dynamic_cast<phy::Spring*>(temp_constraint.get())) {
            Spring spring_copy;
            spring_copy = *spring;

            spring_copy.set_corpse_a(this->get_corpse_by_id(spring_copy.get_corpse_a()->get_id()));
            spring_copy.set_corpse_b(this->get_corpse_by_id(spring_copy.get_corpse_b()->get_id()));

            this->constraints.push_back(std::make_shared<phy::Spring>(spring_copy));
        } else if (phy::Slider* slider = dynamic_cast<phy::Slider*>(temp_constraint.get())) {
            Slider slider_copy;
            slider_copy = *slider;

            slider_copy.set_corpse_a(this->get_corpse_by_id(slider_copy.get_corpse_a()->get_id()));
            slider_copy.set_corpse_b(this->get_corpse_by_id(slider_copy.get_corpse_b()->get_id()));

            for (int i = 0; i < slider_copy.get_slider_corpses_size(); i++) { slider_copy.set_slider_corpse(i, this->get_corpse_by_id(slider_copy.get_slider_corpse(i)->get_id())); }

            this->constraints.push_back(std::make_shared<phy::Slider>(slider_copy));
        }
    }

    return *this;
}

System::~System() {}

void System::Step() {
    bmk::Record("Step");

    this->collisions = {};
    this->quad_pairs = {};

    // Update Positions
    {
        bmk::Record("Corpses");
        CorpsesStep();
    }
    {
        bmk::Record("Forces");
        ForcesStep();
    }
    {
        bmk::Record("Constraints");
        for (int i = 0; i < constraint_accuracy; i++) {
            // std::string label = "Constraint " + i;
            // bmk::Record(label.c_str());
            ConstraintsStep();
        }
    }

    // Check the Limits
    if (this->enable_limits) {
        CheckLimits();
        bmk::Record("Limits");
    }

    // Update Forces
    // Update Velocities
    // Apply Boundaries conditions
    {
        bmk::Record("QuadTree");
        StepQuadTree();
    }

    {
        bmk::Record("Collisions");
        for (int i = 0; i < collision_accuracy; i++) {
            // std::string label = "Collision " + i;
            // bmk::Record("Collision " + com::to_string(i));
            QuadPairsStep();
        }
    }
    {
        bmk::Record("Pairs");
        PairsStep();
    }

    // Move Global Time
    {
        bmk::Record("Time");
        UpdateTime();
    }
}
void System::UpdateTime() { this->t += this->dt; }

void System::CheckLimits() {
    for (int i = 0; i < corpses.size(); i++) {
        if (gmt::BoundsI::BoundsOutBounds(get_corpse(i)->get_bounds(), get_limits())) { Remove(i); }
    }
}

void System::CorpsesStep() {
    for (int i = 0; i < corpses.size(); i++) { get_corpse(i)->Step(); }
}

void System::ForcesStep() {
    for (int i = 0; i < corpses.size(); i++) {
        if (!get_corpse(i)->get_fixed()) { get_corpse(i)->Drag(gmt::VectorI(this->force_x, this->force_y) * this->dt * this->dt); }
    }
}

void System::ConstraintsStep() {
    for (int i = 0; i < constraints.size(); i++) {
        get_constraint(i)->Step();
        if (get_constraint(i)->get_broken()) { com::remove_unordered(i, this->constraints); }
    }
}

void System::CorpseUpdateBounds(int i) {
    if (phy::Circle* circle = dynamic_cast<phy::Circle*>(get_corpse(i).get())) {
        circle->UpdateBounds();
    } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(get_corpse(i).get())) {
        polygon->UpdateBounds();
    }
}

void System::CorpseStop(int i) {
    if (phy::Circle* circle = dynamic_cast<phy::Circle*>(get_corpse(i).get())) {
        circle->Stop();
    } else if (phy::Polygon* polygon = dynamic_cast<phy::Polygon*>(get_corpse(i).get())) {
        polygon->Stop();
    }
}

void System::PairsStep() {
    /*
    // Old broad phase
    for (int i = 0; i < get_corpses_size(); i++) {
        for (int j = i + 1; j < get_corpses_size(); j++) {
            std::vector<gmt::CollisionI> resolved = gmt::CollisionI::Resolve(get_corpse(i), get_corpse(j));
            for (int k = 0; k < resolved.size(); k++) { this->collisions.push_back(resolved[k]); }
        }
    }
    */
    if (this->gravity) {
        for (int i = 0; i < get_corpses_size(); i++) {
            for (int j = i + 1; j < get_corpses_size(); j++) { Gravity(get_corpse(i), get_corpse(j)); }
        }
    }
}

void System::QuadPairsStep() {
    for (int i = 0; i < get_quad_pairs_depth(); i++) {
        int k = 0;
        for (int j = 0; j < quad_pairs[i].second.size(); j++) {
            int node_pairs_size = quad_pairs[i].second[j];
            ThreadPairsStep(i, k, k + node_pairs_size);
            k += node_pairs_size;
        }
    }
}

void System::ThreadPairsStep(int depth, int begin, int end) {
    for (int i = begin; i < end; i++) {
        std::vector<gmt::CollisionI> resolved = gmt::CollisionI::Resolve(this->quad_pairs[depth].first[i].first, this->quad_pairs[depth].first[i].second);
        for (int j = 0; j < resolved.size(); j++) { this->collisions.push_back(resolved[j]); }
    }
}

void System::Clear() {
    this->corpses = {};
    this->constraints = {};
    this->references = {};
}

void System::Remove(int i) {
    std::shared_ptr<Corpse> ptr = com::remove_unordered_return(i, this->corpses);
    com::remove_lambda(this->constraints, [ptr](std::shared_ptr<phy::Constraint> constraint) { return constraint->get_corpse_a() == ptr || constraint->get_corpse_b() == ptr; });
    this->references.erase(ptr->get_id());
}

void System::Gravity(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b) {
    if (a->get_fixed() && b->get_fixed()) { return; }  // Both Fixed

    gmt::UnitI dist = gmt::VectorI::Distance(a->get_pos(), b->get_pos());
    if (dist > gmt::UnitI(MAX_GRAVITY_DISTANCE)) { return; }  // Avoid strange behaviour with big numbers

    // Possible optimisation: Remove the multiplication and division by the mass and
    // just multiply the force by the other body mass when applying it

    gmt::UnitI force = G * a->get_mass() * b->get_mass() / (dist * dist);  // G * (ma * mb)/(r^2)
    if (force > LS) { force = LS; }                                        // Limit with the Light Speed

    gmt::VectorI diff = gmt::VectorI(b->get_pos_x() - a->get_pos_x(), b->get_pos_y() - a->get_pos_y()) / dist;
    gmt::VectorI acceleration_a = diff * force / a->get_mass();
    gmt::VectorI acceleration_b = -diff * force / b->get_mass();

    if (!a->get_fixed()) { a->Drag(acceleration_a * this->dt * this->dt); }
    if (!b->get_fixed()) { b->Drag(acceleration_b * this->dt * this->dt); }
}

void System::StepQuadTree() {
    this->quadtree.Clear();
    for (int i = 0; i < corpses.size(); i++) {
        if (!get_corpse(i)->get_etherial()) { this->quadtree.AddCorpse(get_corpse(i)); }
    }
    this->quad_pairs = this->quadtree.ComputePairs();
    // this->quadtree.Update();
}

gmt::QuadTree* System::get_quadtree() { return &this->quadtree; }

gmt::UnitI System::get_dt() const { return this->dt; }
void System::set_dt(gmt::UnitI dt) {
    // We compute the change in time
    gmt::UnitI dt_diff = dt - this->dt;

    // We need to avoid a dt to close to 0 because
    // it mess up with the corpses velocities.
    // It's better to just pass the area around 0.
    if (!com::float_equals(dt, gmt::UnitI(0), dt_diff / gmt::UnitI(10))) {
        dt = dt + dt_diff;
        dt_diff = dt_diff * gmt::UnitI(2);
    }

    gmt::UnitI dt_frac = dt / this->dt;

    for (int i = 0; i < corpses.size(); i++) {
        // Update corpses velocities an rotations
        get_corpse(i)->set_last_pos(get_corpse(i)->get_pos() - get_corpse(i)->get_diff_pos() * dt_frac);
        get_corpse(i)->set_last_rotation(get_corpse(i)->get_rotation() - get_corpse(i)->get_diff_rotation() * dt_frac);
    }

    this->dt = dt;
}
void System::invert_dt() { this->set_dt(-this->dt); }

double System::get_t() const { return this->t; }
void System::set_t(double t) { this->t = t; }

gmt::UnitI System::get_force_x() const { return this->force_x; }
void System::set_force_x(gmt::UnitI force_x) { this->force_x = force_x; }

gmt::UnitI System::get_force_y() const { return this->force_y; }
void System::set_force_y(gmt::UnitI force_y) { this->force_y = force_y; }

bool System::get_gravity() const { return this->gravity; }
void System::set_gravity(bool gravity) { this->gravity = gravity; }

gmt::UnitI System::get_LS() const { return this->LS; }
void System::set_LS(gmt::UnitI LS) { this->LS = LS; }

gmt::UnitI System::get_G() const { return this->G; }
void System::set_G(gmt::UnitI G) { this->G = G; }

int System::get_collision_accuracy() const { return this->collision_accuracy; }
void System::set_collision_accuracy(int collision_accuracy) { this->collision_accuracy = collision_accuracy; }

int System::get_constraint_accuracy() const { return this->constraint_accuracy; }
void System::set_constraint_accuracy(int constraint_accuracy) { this->constraint_accuracy = constraint_accuracy; }

int System::get_corpses_size() const { return this->corpses.size(); }
int System::get_constraints_size() const { return this->constraints.size(); }

int System::get_pairs_size() const {
    return (get_corpses_size() * (get_corpses_size() - 1)) / 2;  // [n (n - 1)] / 2;
}

int System::get_quad_pairs_depth() const { return this->quad_pairs.size(); }
int System::get_quad_pairs_size() const {
    int size = 0;
    for (int i = 0; i < get_quad_pairs_depth(); i++) { size += this->quad_pairs[i].first.size(); }
    return size;
}
int System::get_quad_pairs_size(int depth) const {
    if (this->quad_pairs.size() < depth + 1) { return 0; }
    return this->quad_pairs[depth].first.size();
}
std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>> System::get_quad_pair(int index, int depth) const { return this->quad_pairs[depth].first[index]; }

void System::addCorpse(Polygon polygon) { add_corpse(std::make_shared<Polygon>(polygon)); }
void System::addCorpse(Circle circle) { add_corpse(std::make_shared<Circle>(circle)); }

void System::addConstraint(Link link) { add_constraint(std::make_shared<Link>(link)); }
void System::addConstraint(Spring spring) { add_constraint(std::make_shared<Spring>(spring)); }
void System::addConstraint(Slider slider) { add_constraint(std::make_shared<Slider>(slider)); }

void System::add_corpse(std::shared_ptr<Corpse> corpse) {
    this->corpses.emplace_back(corpse);
    this->references[corpse->get_id()] = corpse;
}

void System::add_constraint(std::shared_ptr<Constraint> constraint) { this->constraints.emplace_back(std::move(constraint)); }

gmt::BoundsI System::get_limits() const { return this->limits; }
void System::set_limits(gmt::BoundsI limits) {
    this->limits = limits;
    this->quadtree.bounds = limits;
}

std::vector<std::shared_ptr<Corpse>> System::get_corpses() const { return this->corpses; }
std::vector<std::shared_ptr<Constraint>> System::get_constraints() const { return this->constraints; }

std::shared_ptr<Corpse> System::get_corpse(int index) const { return this->corpses[index]; }
std::shared_ptr<Corpse> System::get_corpse_by_id(int index) const {
    auto found = this->references.find(index);
    if (found != this->references.end()) {
        return found->second;
    } else {
        return nullptr;
    }
}
std::shared_ptr<Constraint> System::get_constraint(int index) const { return this->constraints[index]; }

gmt::CollisionI System::get_collision(int index) const { return this->collisions[index]; }
std::vector<gmt::CollisionI> System::get_collisions() const { return this->collisions; }
int System::get_collisions_size() const { return this->collisions.size(); }

bool System::get_enable_limits() const { return this->enable_limits; }
void System::set_enable_limits(bool enable_limits) { this->enable_limits = enable_limits; }

}  // namespace phy
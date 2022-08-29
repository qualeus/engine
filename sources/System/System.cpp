#include "../../include/System/System.hpp"

namespace phy {

System::System() {

    m_integrator  = com::make_sptr<gmt::Euler>(gmt::Euler());
    m_partitioner = com::make_sptr<gmt::BruteForce>(gmt::BruteForce());
    m_solver      = com::make_sptr<gmt::Sequential>(gmt::Sequential());

    m_corpses     = {};
    m_references  = {};
    m_constraints = {};

    m_dt   = 1.0f / 60.0f;
    m_time = 0.0;
}

System::System(const System& other) {
    // TODO
}

System& System::operator=(const System& rhs) {

    // TODO
    return *this;
}

void System::step() {

    for (int i = 0; i < m_corpses.size(); i++) { m_integrator->integrate(m_corpses[i], m_dt); }

    m_time += m_dt;
}

void System::add_corpse(Corpse corpse) {

    m_corpses.push_back(com::make_sptr<Corpse>(corpse));  // copy for lifetime management in the array

    m_references[corpse.get_id()] = m_corpses.back();  // reference in the hashmap to share value access
}

com::sptr<gmt::Integrator> System::get_integrator() const {
    return m_integrator;
}

com::sptr<gmt::Partitioner> System::get_partitioner() const {
    return m_partitioner;
}

com::sptr<gmt::Solver> System::get_solver() const {
    return m_solver;
}

com::vec<com::sptr<Corpse>> System::get_corpses() const {
    return m_corpses;
}

com::map<int, com::sptr<Corpse>> System::get_references() const {
    return m_references;
}

com::vec<com::sptr<Constraint>> System::get_constraints() const {
    return m_constraints;
}

int System::get_corpses_size() const {
    return m_corpses.size();
}

com::sptr<Corpse> System::get_corpse(int index) const {
    return m_corpses[index];
}

com::sptr<Corpse> System::get_corpse_by_id(int id) const {
    auto found = m_references.find(id);

    if (found != m_references.end()) { return found->second; }

    LOG_ERROR("Index is not referenced in the system corpses reference map");
}

double System::get_time() const {
    return m_time;
}
double System::get_dt() const {
    return m_dt;
}

}  // namespace phy
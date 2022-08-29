#ifndef System_HPP
#define System_HPP

// GLOBAL CONFIG
#include "Config.hpp"

// GLOBAL UTILS
#include "../Common/Maths.hpp"
#include "../Common/String.hpp"
#include "../Geometry/Geometry.hpp"

// CONSTRAINTS
#include "../Constraints/Link.hpp"

// COLLISIONS
#include "../Collisions/Collision.hpp"

// CORPSES
#include "../Corpses/Circle.hpp"
#include "../Corpses/Polygon.hpp"

// PARTITIONNERS
#include "../Partitioners/BruteForce.hpp"

// INTEGRATORS
#include "../Integrators/Euler.hpp"

// SOLVERS
#include "../Solvers/Sequential.hpp"

namespace phy {

class System {
   private:
    com::sptr<gmt::Integrator> m_integrator;
    com::sptr<gmt::Partitioner> m_partitioner;
    com::sptr<gmt::Solver> m_solver;

    com::vec<com::sptr<Corpse>> m_corpses;
    com::map<int, com::sptr<Corpse>> m_references;

    com::vec<com::sptr<Constraint>> m_constraints;

    double m_dt;
    double m_time;

   public:
    System();

    System(const System& other);

    System& operator=(const System& rhs);

    void step();
    void add_corpse(Corpse corpse);

    com::sptr<gmt::Integrator> get_integrator() const;
    com::sptr<gmt::Partitioner> get_partitioner() const;
    com::sptr<gmt::Solver> get_solver() const;
    com::vec<com::sptr<Corpse>> get_corpses() const;
    com::map<int, com::sptr<Corpse>> get_references() const;
    com::vec<com::sptr<Constraint>> get_constraints() const;

    int get_corpses_size() const;
    com::sptr<Corpse> get_corpse(int index) const;
    com::sptr<Corpse> get_corpse_by_id(int id) const;

    double get_time() const;
    double get_dt() const;
};

}  // namespace phy

#endif
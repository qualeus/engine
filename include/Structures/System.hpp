#ifndef System_HPP
#define System_HPP

#include "../Common/Maths.hpp"
#include "../Constraints/Constraint.hpp"
#include "../Constraints/Link.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Collision.hpp"
#include "../Geometry/Geometry.hpp"
#include "Config.hpp"
#include "QuadTree.hpp"

namespace phy {

class System {
   private:
    std::vector<std::shared_ptr<Corpse>> m_corpses;
    std::vector<std::shared_ptr<Constraint>> m_constraints;
    std::unordered_map<int, std::shared_ptr<Corpse>> m_references;

    std::vector<gmt::NodePairs> m_quad_pairs;
    std::vector<gmt::CollisionI> m_collisions;

    gmt::QuadTree m_quadtree;
    gmt::BoundsI m_limits;

    bool m_gravity;
    bool m_enable_limits;
    gmt::UnitI m_ls = 2.998e+8;  // 2,998 * 10e+8
    gmt::UnitI m_g = 1.6e-2;     // 6.7 * 10e-11

    gmt::UnitI m_force_x;
    gmt::UnitI m_force_y;

    gmt::UnitI m_dt = 1.0f;
    double m_t = 0.0;

    int m_collision_accuracy = 10;
    int m_constraint_accuracy = 1;

   public:
    System(bool gravity = false,
           gmt::UnitI force_x = gmt::UnitI(0),
           gmt::UnitI force_y = gmt::UnitI(0),
           gmt::UnitI limit_x = gmt::UnitI(10000),
           gmt::UnitI limit_y = gmt::UnitI(10000),
           int quadtree_max_count = 10,
           int quadtree_max_depth = 10);

    System(const System& other);

    System& operator=(const System& rhs);
    virtual ~System();

    void step();
    void update_time();
    void check_limits();
    void corpses_step();
    void forces_step();
    void constraints_step();
    void corpse_stop(int i);
    void corpse_update_bounds(int i);
    void pairs_step();
    void quad_pairs_step();
    void thread_pairs_step(int depth, int begin, int end);
    void remove(int i);
    void clear();

    void gravity(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b);

    void init_quad_tree();
    void step_quad_tree();
    gmt::QuadTree* get_quadtree();

    gmt::UnitI get_dt() const;
    void set_dt(gmt::UnitI dt);
    void invert_dt();

    double get_t() const;
    void set_t(double t);

    gmt::UnitI get_force_x() const;
    void set_force_x(gmt::UnitI force_x);

    gmt::UnitI get_force_y() const;
    void set_force_y(gmt::UnitI force_y);

    bool get_gravity() const;
    void set_gravity(bool gravity);

    gmt::UnitI get_ls() const;
    void set_ls(gmt::UnitI LS);

    gmt::UnitI get_g() const;
    void set_g(gmt::UnitI G);

    int get_collision_accuracy() const;
    void set_collision_accuracy(int collision_accuracy);

    int get_constraint_accuracy() const;
    void set_constraint_accuracy(int constraint_accuracy);

    int get_corpses_size() const;
    int get_constraints_size() const;

    int get_pairs_size() const;

    int get_quad_pairs_depth() const;
    int get_quad_pairs_size() const;
    int get_quad_pairs_size(int depth) const;

    void add_corpse(Polygon polygon);
    void add_corpse(Circle circle);
    void add_corpse(std::shared_ptr<Corpse> corpse);

    void add_constraint(Link link);
    void add_constraint(std::shared_ptr<Constraint> constraint);

    gmt::BoundsI get_limits() const;
    void set_limits(gmt::BoundsI limits);

    std::vector<std::shared_ptr<Corpse>> get_corpses() const;
    std::vector<std::shared_ptr<Constraint>> get_constraints() const;

    std::shared_ptr<Corpse> get_corpse(int index) const;
    std::shared_ptr<Corpse> get_corpse_by_id(int index) const;
    std::shared_ptr<Constraint> get_constraint(int index) const;

    gmt::CollisionI get_collision(int index) const;
    std::vector<gmt::CollisionI> get_collisions() const;
    int get_collisions_size() const;

    std::pair<std::shared_ptr<Corpse>, std::shared_ptr<Corpse>> get_quad_pair(int index, int depth) const;

    bool get_enable_limits() const;
    void set_enable_limits(bool enable_limits);
};

}  // namespace phy

#endif
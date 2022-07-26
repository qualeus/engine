#ifndef System_HPP
#define System_HPP

#include "../Common/Maths.hpp"
#include "../Constraints/Constraint.hpp"
#include "../Constraints/Link.hpp"
#include "../Constraints/Slider.hpp"
#include "../Constraints/Spring.hpp"
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
    std::vector<std::shared_ptr<Corpse>> corpses;
    std::vector<std::shared_ptr<Constraint>> constraints;
    std::unordered_map<int, std::shared_ptr<Corpse>> references;

    std::vector<gmt::NodePairs> quad_pairs;
    std::vector<gmt::CollisionI> collisions;

    gmt::QuadTree quadtree;
    gmt::BoundsI limits;

    bool gravity;
    bool enable_limits;
    gmt::UnitI LS = 2.998e+8;  // 2,998 * 10e+8
    gmt::UnitI G = 1.6e-2;     // 6.7 * 10e-11

    gmt::UnitI force_x;
    gmt::UnitI force_y;

    gmt::UnitI dt = 1.0f;
    double t = 0.0;

    int collision_accuracy = 10;
    int constraint_accuracy = 1;

   public:
    System(bool gravity = false,                    //
           gmt::UnitI force_x = gmt::UnitI(0),      //
           gmt::UnitI force_y = gmt::UnitI(0),      //
           gmt::UnitI limit_x = gmt::UnitI(10000),  //
           gmt::UnitI limit_y = gmt::UnitI(10000),  //
           int quadtree_max_count = 10,             //
           int quadtree_max_depth = 10);            //

    System(const System& other);

    System& operator=(const System& rhs);
    virtual ~System();

    void Step();
    void UpdateTime();
    void CheckLimits();
    void CorpsesStep();
    void ForcesStep();
    void ConstraintsStep();
    void CorpseStop(int i);
    void CorpseUpdateBounds(int i);
    void PairsStep();
    void QuadPairsStep();
    void ThreadPairsStep(int depth, int begin, int end);
    void Remove(int i);
    void Clear();

    void Gravity(std::shared_ptr<Corpse> a, std::shared_ptr<Corpse> b);

    void InitQuadTree();
    void StepQuadTree();
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

    gmt::UnitI get_LS() const;
    void set_LS(gmt::UnitI LS);

    gmt::UnitI get_G() const;
    void set_G(gmt::UnitI G);

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

    void addCorpse(Polygon polygon);
    void addCorpse(Circle circle);

    void addConstraint(Link link);
    void addConstraint(Spring spring);
    void addConstraint(Slider slider);

    void add_constraint(std::shared_ptr<Constraint> constraint);

    void add_corpse(std::shared_ptr<Corpse> corpse);

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
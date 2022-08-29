#ifndef QuadTree_HPP
#define QuadTree_HPP

#include "../Common/Maths.hpp"
#include "../Common/String.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Bounds.hpp"
#include "../Geometry/Vector2.hpp"
#include "Partitioner.hpp"

namespace gmt {

class QuadNode {
   public:
    com::arr<com::uptr<QuadNode>, 4> childs;
    com::vec<com::sptr<phy::Corpse>> corpses;
    QuadNode& operator=(const QuadNode& rhs);

    QuadNode();

    bool is_leaf();
};

class QuadTree : public Partitioner {
   private:
    void split_node(QuadNode* node, const BoundsI& bounds);

    BoundsI compute_node_bounds(const BoundsI& bounds, int index) const;
    BoundsI compute_corpse_bounds(const com::sptr<phy::Corpse>& corpse) const;

    int quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const;

    void add_corpse(int depth, QuadNode* node, const BoundsI& node_bounds, com::sptr<phy::Corpse> corpse, const BoundsI& corpse_bounds);
    void clear_node(QuadNode* node);

    void compute_node_pairs(QuadNode* node, com::vec<com::spair<com::sptr<phy::Corpse>>>& pairs, com::vec<com::sptr<phy::Corpse>>& above) const;

   public:
    int max_count;
    int max_depth;
    BoundsI limits;
    com::uptr<QuadNode> root;

    QuadTree& operator=(const QuadTree& rhs);
    QuadTree(const BoundsI& limits = BoundsI(), const int& max_count = 12, const int& max_depth = 10);
    QuadTree(const QuadTree& quadtree);

    void clear();

    void add_corpse(com::sptr<phy::Corpse> corpse);

    com::vec<com::spair<com::sptr<phy::Corpse>>> compute_pairs(com::vec<com::sptr<phy::Corpse>> corpses);

    void find_bounds(QuadNode* node, const BoundsI& node_bounds, com::vec<BoundsI>& bounds) const;
    com::vec<BoundsI> compute_bounds() const;
};

}  // namespace gmt

#endif
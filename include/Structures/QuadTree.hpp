#ifndef QuadTree_HPP
#define QuadTree_HPP

#include "../Common/Maths.hpp"
#include "../Common/String.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Bounds.hpp"
#include "../Geometry/Vector2.hpp"
#include "QuadNode.hpp"

namespace gmt {

/*
    To parallelize the quadtree, we need to decompose the layers in subcells that we are sure don't interact with each others
     * for the lowest levels (leafs) we know only the inside objects can interact so we save for each node the number of pairs
     * for the uppers levels, we have to care that the pairs with sub-levels don't interact n the same object, we can keep the
       same logic by decomposing the pairs by levels with the depths and recording the number of pairs in this current node...
     * then we only have to climb these layers while parallelizing the nodes...
*/
using NodePairs = std::pair<std::vector<std::pair<std::shared_ptr<phy::Corpse>, std::shared_ptr<phy::Corpse>>>, std::vector<int>>;

class QuadTree {
   private:
    void split_node(QuadNode* node, const BoundsI& bounds);

    BoundsI compute_node_bounds(const BoundsI& bounds, int index) const;
    BoundsI compute_corpse_bounds(const std::shared_ptr<phy::Corpse>& corpse) const;

    int quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const;

    void add(int depth, QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds);
    void remove(QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds);
    void search_remove(QuadNode* node, std::shared_ptr<phy::Corpse> corpse);
    void cleanup_node(QuadNode* node);
    void clear_node(QuadNode* node);

   public:
    int max_count;
    int max_depth;
    BoundsI limits;
    std::unique_ptr<QuadNode> root;

    QuadTree& operator=(const QuadTree& rhs);
    QuadTree(const BoundsI& limits = BoundsI(), const int& max_count = 12, const int& max_depth = 10);
    QuadTree(const QuadTree& quadtree);
    // ~QuadTree();

    void clear();

    void add_corpse(std::shared_ptr<phy::Corpse> corpse);

    void find_pairs(QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const;
    void childs_pairs(const std::vector<std::shared_ptr<phy::Corpse>>& corpses, QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const;
    std::vector<gmt::NodePairs> compute_pairs() const;

    void find_bounds(QuadNode* node, const BoundsI& node_bounds, std::vector<BoundsI>& bounds) const;
    std::vector<BoundsI> compute_bounds() const;
};

}  // namespace gmt

#endif
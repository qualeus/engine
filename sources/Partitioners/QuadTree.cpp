#include "../../include/Partitioners/QuadTree.hpp"

namespace gmt {

/* ====================== QUADNODE ========================= */

/* Vectors Operators: QuadNode=Copy */
QuadNode& QuadNode::operator=(const QuadNode& rhs) {
    return *this;
}

/* Builder Constructor */
QuadNode::QuadNode() {
    childs  = {nullptr, nullptr, nullptr, nullptr};
    corpses = {};
}

bool QuadNode::is_leaf() {
    return !static_cast<bool>(childs[0]);
}

/* Vectors Operators: QuadTree=Copy */
QuadTree& QuadTree::operator=(const QuadTree& rhs) {
    return *this;
}

/* ====================== QUADTREE ========================= */

/* Builder Constructor */
QuadTree::QuadTree(const BoundsI& _limits, const int& _max_count, const int& _max_depth) {
    limits    = _limits;
    max_count = _max_count;
    max_depth = _max_depth;

    root = std::make_unique<QuadNode>();
}

QuadTree::QuadTree(const QuadTree& quadtree) {
    limits    = quadtree.limits;
    max_count = quadtree.max_count;
    max_depth = quadtree.max_depth;

    root = std::make_unique<QuadNode>();
}

void QuadTree::split_node(QuadNode* node, const BoundsI& bounds) {
    // Initialize the children nodes
    for (int i = 0; i < 4; i++) { node->childs[i] = std::make_unique<QuadNode>(); }

    // Assign the corpses to the childs
    com::vec<com::sptr<phy::Corpse>> new_corpses = {};

    for (int i = 0; i < node->corpses.size(); i++) {
        const com::sptr<phy::Corpse> corpse = node->corpses[i];

        const BoundsI corpse_bounds = compute_corpse_bounds(corpse);

        int index = quadrant(bounds, corpse_bounds);

        if (index == -1) {
            new_corpses.push_back(corpse);
        } else {
            node->childs[index]->corpses.push_back(corpse);
        }
    }

    node->corpses = std::move(new_corpses);
}

BoundsI QuadTree::compute_node_bounds(const BoundsI& bounds, int index) const {
    UnitI midx = bounds.p1.x + (bounds.p2.x - bounds.p1.x) / UnitI(2);
    UnitI midy = bounds.p1.y + (bounds.p2.y - bounds.p1.y) / UnitI(2);

    switch (index) {
        case 0: return BoundsI(bounds.p1.x, bounds.p1.y, midx, midy);  // NW
        case 1: return BoundsI(midx, bounds.p1.y, bounds.p2.x, midy);  // NE
        case 2: return BoundsI(bounds.p1.x, midy, midx, bounds.p2.y);  // SW
        case 3: return BoundsI(midx, midy, bounds.p2.x, bounds.p2.y);  // SE
    }

    LOG_ERROR("Out of range, index given is " + com::to_string(index) + " but only 4 Sub-Nodes");
}

BoundsI QuadTree::compute_corpse_bounds(const com::sptr<phy::Corpse>& corpse) const {
    return compute_corpse_bounds(corpse);
}

int QuadTree::quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const {
    UnitI midx = node_bounds.p1.x + (node_bounds.p2.x - node_bounds.p1.x) / UnitI(2);
    UnitI midy = node_bounds.p1.y + (node_bounds.p2.y - node_bounds.p1.y) / UnitI(2);

    bool pos_left  = corpse_bounds.p1.x < midx && corpse_bounds.p2.x < midx;
    bool pos_right = corpse_bounds.p1.x >= midx;

    if (corpse_bounds.p1.y < midy && corpse_bounds.p2.y < midy) {
        if (pos_left) return 0;
        if (pos_right) return 1;
    } else if (corpse_bounds.p1.y >= midy) {
        if (pos_left) return 2;
        if (pos_right) return 3;
    }

    return -1;  // The corpse intersect with the node bounds
}

void QuadTree::add_corpse(com::sptr<phy::Corpse> corpse) {
    add_corpse(0, root.get(), limits, corpse, compute_corpse_bounds(corpse));
}

void QuadTree::add_corpse(int depth, QuadNode* node, const BoundsI& node_bounds, com::sptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {

    if (node->is_leaf()) {
        if (depth > max_depth) {

            node->corpses.push_back(corpse);  // Can't descend further more

        } else if (node->corpses.size() < max_count) {

            node->corpses.push_back(corpse);  // Still room in the node

        } else {
            split_node(node, node_bounds);
            add_corpse(depth, node, node_bounds, corpse, corpse_bounds);
        }

    } else {

        int index = quadrant(node_bounds, corpse_bounds);

        if (index == -1) {

            node->corpses.push_back(corpse);  // Can't fit the corpse in a sub node

        } else {

            add_corpse(depth + 1, node->childs[index].get(), compute_node_bounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::find_bounds(QuadNode* node, const BoundsI& node_bounds, com::vec<BoundsI>& bounds) const {
    bounds.push_back(node_bounds);

    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) { find_bounds(node->childs[i].get(), compute_node_bounds(node_bounds, i), bounds); }
    }
}

void QuadTree::clear() {
    clear_node(root.get());
}

void QuadTree::clear_node(QuadNode* node) {
    node->corpses = {};
    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) {
            clear_node(node->childs[i].get());
            node->childs[i] = nullptr;
        }
    }
}

void QuadTree::compute_node_pairs(QuadNode* node, com::vec<com::spair<com::sptr<phy::Corpse>>>& pairs, com::vec<com::sptr<phy::Corpse>>& above) const {
    const int corpse_size = node->corpses.size();
    const int above_size  = above.size();

    // Internal pairs
    for (int i = 0; i < corpse_size; i++) {
        for (int j = i + 1; j < corpse_size; j++) { pairs.push_back({node->corpses[i], node->corpses[j]}); }
    }

    // External pairs
    for (int i = 0; i < above_size; i++) {
        for (int j = 0; j < corpse_size; j++) { pairs.push_back({above[i], node->corpses[j]}); }
    }

    // Update above with currents
    for (int i = 0; i < corpse_size; i++) { above.push_back(node->corpses[i]); }

    // Sub nodes pairs
    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) { compute_node_pairs(node->childs[i].get(), pairs, above); }
    }

    // Remove added above (allow to avoid full array copy)
    for (int i = 0; i < corpse_size; i++) { above.pop_back(); }
}

com::vec<BoundsI> QuadTree::compute_bounds() const {
    com::vec<BoundsI> bounds = {};
    find_bounds(root.get(), limits, bounds);
    return bounds;
}

com::vec<com::spair<com::sptr<phy::Corpse>>> QuadTree::compute_pairs(com::vec<com::sptr<phy::Corpse>> corpses) {

    // insert coprses
    for (int i = 0; i < corpses.size(); i++) { add_corpse(corpses[i]); }

    // extract pairs
    com::vec<com::spair<com::sptr<phy::Corpse>>> pairs = {};
    com::vec<com::sptr<phy::Corpse>> above             = {};

    compute_node_pairs(root.get(), pairs, above);

    // clear the tree
    clear();

    return pairs;
}

}  // namespace gmt
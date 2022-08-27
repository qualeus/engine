#include "../../include/Structures/QuadTree.hpp"

namespace gmt {

/* Vectors Operators: QuadTree=Copy */
QuadTree& QuadTree::operator=(const QuadTree& rhs) {
    return *this;
}

/* Builder Constructor */
QuadTree::QuadTree(const BoundsI& _limits, const int& _max_count, const int& _max_depth) {
    limits = _limits;
    max_count = _max_count;
    max_depth = _max_depth;

    root = std::make_unique<QuadNode>();
}

QuadTree::QuadTree(const QuadTree& quadtree) {
    limits = quadtree.limits;
    max_count = quadtree.max_count;
    max_depth = quadtree.max_depth;

    root = std::make_unique<QuadNode>();
}

/* Default Destructor */
// QuadTree::~QuadTree() {}

void QuadTree::split_node(QuadNode* node, const BoundsI& bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    // if (!node->Leaf()) { throw std::invalid_argument(); }

    // Initialize the children nodes
    for (int i = 0; i < 4; i++) { node->childs[i] = std::make_unique<QuadNode>(); }

    // Assign the corpses to the childs
    std::vector<std::shared_ptr<phy::Corpse>> new_corpses = {};

    for (int i = 0; i < node->corpses.size(); i++) {
        const std::shared_ptr<phy::Corpse> corpse = node->corpses[i];
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
    UnitI midx = bounds.x1 + (bounds.x2 - bounds.x1) / UnitI(2);
    UnitI midy = bounds.y1 + (bounds.y2 - bounds.y1) / UnitI(2);
    switch (index) {
        case 0: return BoundsI(bounds.x1, bounds.y1, midx, midy);   // NW
        case 1: return BoundsI(midx, bounds.y1, bounds.x2, midy);   // NE
        case 2: return BoundsI(bounds.x1, midy, +midx, bounds.y2);  // SW
        case 3: return BoundsI(midx, midy, bounds.x2, bounds.y2);   // SE
    }
    LOG_ERROR("Out of range, index given is " + com::to_string(index) + " but only 4 Sub-Nodes");
}

BoundsI QuadTree::compute_corpse_bounds(const std::shared_ptr<phy::Corpse>& corpse) const {
    return compute_corpse_bounds(corpse);
}

int QuadTree::quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const {
    UnitI midx = node_bounds.x1 + (node_bounds.x2 - node_bounds.x1) / UnitI(2);
    UnitI midy = node_bounds.y1 + (node_bounds.y2 - node_bounds.y1) / UnitI(2);

    // bool pos_top = corpse_bounds.y1 < midy && corpse_bounds.y2 < midy;
    // bool pos_bot = corpse_bounds.y1 >= midy;
    bool pos_left = corpse_bounds.x1 < midx && corpse_bounds.x2 < midx;
    bool pos_right = corpse_bounds.x1 >= midx;

    int index = -1;  // The corpse intersect with the node bounds

    if (corpse_bounds.y1 < midy && corpse_bounds.y2 < midy) {
        if (pos_left) {
            index = 0;
        } else if (pos_right) {
            index = 1;
        }
    } else if (corpse_bounds.y1 >= midy) {
        if (pos_left) {
            index = 2;
        } else if (pos_right) {
            index = 3;
        }
    }

    return index;
}

void QuadTree::add_corpse(std::shared_ptr<phy::Corpse> corpse) {
    add(0, root.get(), limits, corpse, compute_corpse_bounds(corpse));
}

void QuadTree::add(int depth, QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    if (node->is_leaf()) {
        if (depth > max_depth) {
            node->corpses.push_back(corpse);  // Can't descend further more
        } else if (node->corpses.size() < max_count) {
            node->corpses.push_back(corpse);  // Still room in the node
        } else {
            split_node(node, node_bounds);
            add(depth, node, node_bounds, corpse, corpse_bounds);
        }
    } else {
        int index = quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            node->corpses.push_back(corpse);  // Can't fit the corpse in a sub node
        } else {
            add(depth + 1, node->childs[index].get(), compute_node_bounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::remove(QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }

    if (node->is_leaf()) {
        search_remove(node, corpse);
    } else {
        int index = quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            search_remove(node, corpse);
        } else {
            remove(node->childs[index].get(), compute_node_bounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::search_remove(QuadNode* node, std::shared_ptr<phy::Corpse> corpse) {
    auto it = std::find_if(std::begin(node->corpses), std::end(node->corpses), [this, &corpse](const std::shared_ptr<phy::Corpse>& rhs) { return corpse == rhs; });

    if (it == std::end(node->corpses)) { LOG_ERROR("Object don't exists in the Node"); }  // trying to repove an object that don't exist in the node

    *it = std::move(node->corpses.back());
    node->corpses.pop_back();
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

void QuadTree::find_bounds(QuadNode* node, const BoundsI& node_bounds, std::vector<BoundsI>& bounds) const {
    bounds.push_back(node_bounds);
    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) { find_bounds(node->childs[i].get(), compute_node_bounds(node_bounds, i), bounds); }
    }
}

void QuadTree::clear() {
    clear_node(root.get());
}

std::vector<gmt::NodePairs> QuadTree::compute_pairs() const {
    std::vector<gmt::NodePairs> pairs = {{{}, {}}};
    find_pairs(root.get(), pairs, 0);
    return pairs;
}

void QuadTree::find_pairs(QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const {
    const int corpse_size = node->corpses.size();
    if (corpse_size > 1) {
        int pairs_size = 0;
        for (int a = 0; a < corpse_size; a++) {
            for (int b = a + 1; b < corpse_size; b++) {
                pairs[0].first.push_back({node->corpses[a], node->corpses[b]});  // Internal pairs
                pairs_size++;
            }
        }
        pairs[0].second.push_back(pairs_size);  // Node Internal pairs size
    }

    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) {
            find_pairs(node->childs[i].get(), pairs, depth + 1);                   // Find Internals pairs between the Child nodes corpses
            childs_pairs(node->corpses, node->childs[i].get(), pairs, depth + 1);  // Find pairs between this nodes corpses and child corpses
        }
    }
}

void QuadTree::childs_pairs(const std::vector<std::shared_ptr<phy::Corpse>>& corpses, QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const {
    const int parent_size = corpses.size();
    const int corpse_size = node->corpses.size();

    while (pairs.size() < depth + 1) { pairs.push_back({{}, {}}); }

    if (!node->is_leaf()) {
        for (int i = 0; i < 4; i++) { childs_pairs(com::concatenate(corpses, node->corpses), node->childs[i].get(), pairs, depth + 1); }
    }

    // PROBLEM : pairs duplication
    if (parent_size > 0 && corpse_size > 0) {
        int pairs_size = 0;
        for (int a = 0; a < parent_size; a++) {
            for (int b = 0; b < corpse_size; b++) {
                pairs[depth].first.push_back({corpses[a], node->corpses[b]});  // Get the pair
                pairs_size++;
            }
        }
        pairs[depth].second.push_back(pairs_size);  // save the size of pairs for this depth
    }
}

std::vector<BoundsI> QuadTree::compute_bounds() const {
    std::vector<BoundsI> bounds = {};
    find_bounds(root.get(), limits, bounds);
    return bounds;
}

}  // namespace gmt
#include "../../include/Structures/QuadTree.hpp"

namespace gmt {

/* Vectors Operators: QuadTree=Copy */
QuadTree& QuadTree::operator=(const QuadTree& rhs) { return *this; }

/* Builder Constructor */
QuadTree::QuadTree(const BoundsI& bounds, const int& max_count, const int& max_depth) {
    this->bounds = bounds;
    this->max_count = max_count;
    this->max_depth = max_depth;

    this->root = std::make_unique<QuadNode>();
}

QuadTree::QuadTree(const QuadTree& quadtree) {
    this->bounds = quadtree.bounds;
    this->max_count = quadtree.max_count;
    this->max_depth = quadtree.max_depth;

    this->root = std::make_unique<QuadNode>();
}

/* Default Destructor */
// QuadTree::~QuadTree() {}

void QuadTree::SplitNode(QuadNode* node, const BoundsI& bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    // if (!node->Leaf()) { throw std::invalid_argument(); }

    // Initialize the children nodes
    for (int i = 0; i < 4; i++) { node->childs[i] = std::make_unique<QuadNode>(); }

    // Assign the corpses to the childs
    std::vector<std::shared_ptr<phy::Corpse>> new_corpses = {};

    for (int i = 0; i < node->corpses.size(); i++) {
        const std::shared_ptr<phy::Corpse> corpse = node->corpses[i];
        const BoundsI corpse_bounds = CorpseBounds(corpse);

        int index = Quadrant(bounds, corpse_bounds);

        if (index == -1) {
            new_corpses.push_back(corpse);
        } else {
            node->childs[index]->corpses.push_back(corpse);
        }
    }

    node->corpses = std::move(new_corpses);
}

BoundsI QuadTree::NodeBounds(const BoundsI& bounds, int index) const {
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

BoundsI QuadTree::CorpseBounds(const std::shared_ptr<phy::Corpse>& corpse) const { return corpse->get_bounds(); }

int QuadTree::Quadrant(const BoundsI& node_bounds, const BoundsI& corpse_bounds) const {
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

void QuadTree::AddCorpse(std::shared_ptr<phy::Corpse> corpse) { Add(0, root.get(), bounds, corpse, CorpseBounds(corpse)); }

void QuadTree::Add(int depth, QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }
    if (node->Leaf()) {
        if (depth > max_depth) {
            node->corpses.push_back(corpse);  // Can't descend further more
        } else if (node->corpses.size() < max_count) {
            node->corpses.push_back(corpse);  // Still room in the node
        } else {
            SplitNode(node, node_bounds);
            Add(depth, node, node_bounds, corpse, corpse_bounds);
        }
    } else {
        int index = Quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            node->corpses.push_back(corpse);  // Can't fit the corpse in a sub node
        } else {
            Add(depth + 1, node->childs[index].get(), NodeBounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::Remove(QuadNode* node, const BoundsI& node_bounds, std::shared_ptr<phy::Corpse> corpse, const BoundsI& corpse_bounds) {
    // if (node == nullptr) { throw std::bad_weak_ptr(); }

    if (node->Leaf()) {
        SearchRemove(node, corpse);
    } else {
        int index = Quadrant(node_bounds, corpse_bounds);
        if (index == -1) {
            SearchRemove(node, corpse);
        } else {
            Remove(node->childs[index].get(), NodeBounds(node_bounds, index), corpse, corpse_bounds);
        }
    }
}

void QuadTree::SearchRemove(QuadNode* node, std::shared_ptr<phy::Corpse> corpse) {
    auto it = std::find_if(std::begin(node->corpses), std::end(node->corpses), [this, &corpse](const std::shared_ptr<phy::Corpse>& rhs) { return corpse == rhs; });

    if (it == std::end(node->corpses)) { LOG_ERROR("Object don't exists in the Node"); }  // trying to repove an object that don't exist in the node

    *it = std::move(node->corpses.back());
    node->corpses.pop_back();
}

void QuadTree::CleanupNode(QuadNode* node) {
    if (!node->Leaf()) {
        int leaf_count = 0;
        for (int i = 0; i < 4; i++) {
            if (node->childs[i]->Leaf() && node->corpses.size() == 0) {
                leaf_count++;
            } else {
                CleanupNode(node->childs[i].get());
            }
        }

        if (leaf_count == 4) { node->childs = {nullptr, nullptr, nullptr, nullptr}; }
    }
}

void QuadTree::ClearNode(QuadNode* node) {
    node->corpses = {};
    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) {
            ClearNode(node->childs[i].get());
            node->childs[i] = nullptr;
        }
    }
}

void QuadTree::FindBounds(QuadNode* node, const BoundsI& node_bounds, std::vector<BoundsI>& bounds) const {
    bounds.push_back(node_bounds);
    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) { FindBounds(node->childs[i].get(), NodeBounds(node_bounds, i), bounds); }
    }
}

void QuadTree::RemoveCorpse(std::shared_ptr<phy::Corpse> corpse) {
    // TODO
}

void QuadTree::Update() {
    // Move up all the corpses that moved / are overflowing (ascending)
    if (!root->Leaf()) {
        for (int i = 0; i < 4; i++) { AscendingUpdate(root->childs[i].get(), root.get(), NodeBounds(this->bounds, i)); }
    }

    // When we have pushed up all the corpses that could be, we test if we can push back
    DescendingUpdate(0, root.get(), bounds);

    Cleanup();
}

std::vector<gmt::BoundsI> QuadTree::AscendingUpdate(QuadNode* node, QuadNode* parent, const gmt::BoundsI& bounds) {
    std::vector<gmt::BoundsI> corpses_bounds;

    // Push up corpses that are moving to another node and compute their bounds
    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) {
            std::vector<gmt::BoundsI> node_corpses_bounds = AscendingUpdate(node->childs[i].get(), node, NodeBounds(bounds, i));
            std::vector<gmt::BoundsI> temp_bounds = com::concatenate(corpses_bounds, node_corpses_bounds);
            corpses_bounds = temp_bounds;
        }
    }

    // Compute the bounds for the corpses that were already in that node
    std::vector<gmt::BoundsI> node_corpses_bounds;
    for (int i = 0; i < node->corpses.size() - corpses_bounds.size(); i++) {
        const std::shared_ptr<phy::Corpse> corpse = node->corpses[i];
        BoundsI corpse_bounds = CorpseBounds(corpse);
        node_corpses_bounds.push_back(corpse_bounds);
    }

    // Put the compute bounds in the right order (current :: childs)
    std::vector<gmt::BoundsI> temp_bounds = com::concatenate(node_corpses_bounds, corpses_bounds);
    corpses_bounds = temp_bounds;

    // Check the corpses that are still moving to another node
    std::vector<int> to_push_up = {};
    for (int i = 0; i < corpses_bounds.size(); i++) {
        if (!gmt::BoundsI::BoundsInBounds(corpses_bounds[i], bounds)) { to_push_up.push_back(i); }
    }

    // Push the corpses in the parent node and record their bounds
    std::vector<gmt::BoundsI> moving_bounds = {};
    for (int i = 0; i < to_push_up.size(); i++) {
        moving_bounds.push_back(corpses_bounds[i]);

        // TO ADAPT? easely with erase but seems harder to keep trace of ids with move_back...
        std::shared_ptr<phy::Corpse> push_up_corpse = com::remove_return(to_push_up[i] - i, node->corpses);  // -i is because we remove one each time

        // Push into parent corpses
        parent->corpses.push_back(push_up_corpse);
    }

    // Return the bounds of the objects that were pushed up
    return moving_bounds;
}

void QuadTree::DescendingUpdate(int depth, QuadNode* node, const gmt::BoundsI& node_bounds) {
    if (!node->Leaf()) {
        // for (int i = 0; i < 4; i++) { DescendingUpdate(depth + 1, node->childs[i].get(), NodeBounds(node_bounds, i)); }
    }

    for (int i = 0; i < node->corpses.size(); i++) {
        // BoundsI corpse_bounds = CorpseBounds(node->corpses[i]);
        // Add(depth, node, node_bounds, node->corpses[i], corpse_bounds);
    }
}

void QuadTree::Cleanup() { CleanupNode(root.get()); }

void QuadTree::Clear() { ClearNode(root.get()); }

std::vector<gmt::NodePairs> QuadTree::ComputePairs() const {
    std::vector<gmt::NodePairs> pairs = {{{}, {}}};
    FindPairs(root.get(), pairs, 0);
    return pairs;
}

void QuadTree::FindPairs(QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const {
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

    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) {
            FindPairs(node->childs[i].get(), pairs, depth + 1);                   // Find Internals pairs between the Child nodes corpses
            ChildsPairs(node->corpses, node->childs[i].get(), pairs, depth + 1);  // Find pairs between this nodes corpses and child corpses
        }
    }
}

void QuadTree::ChildsPairs(const std::vector<std::shared_ptr<phy::Corpse>>& corpses, QuadNode* node, std::vector<gmt::NodePairs>& pairs, int depth) const {
    const int parent_size = corpses.size();
    const int corpse_size = node->corpses.size();

    while (pairs.size() < depth + 1) { pairs.push_back({{}, {}}); }

    if (!node->Leaf()) {
        for (int i = 0; i < 4; i++) { ChildsPairs(com::concatenate(corpses, node->corpses), node->childs[i].get(), pairs, depth + 1); }
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

std::vector<BoundsI> QuadTree::ComputeBounds() const {
    std::vector<BoundsI> bounds = {};
    FindBounds(root.get(), this->bounds, bounds);
    return bounds;
}

}  // namespace gmt
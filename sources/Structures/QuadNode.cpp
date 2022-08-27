#include "../../include/Structures/QuadNode.hpp"

namespace gmt {

/* Vectors Operators: QuadTree=Copy */
QuadNode& QuadNode::operator=(const QuadNode& rhs) {
    return *this;
}

/* Builder Constructor */
QuadNode::QuadNode() {
    childs = {nullptr, nullptr, nullptr, nullptr};
    corpses = {};
}

/* Default Destructor */
// QuadNode::~QuadNode() {}

bool QuadNode::is_leaf() {
    return !static_cast<bool>(childs[0]);
}

}  // namespace gmt
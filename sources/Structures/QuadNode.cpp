#include "../../include/Structures/QuadNode.hpp"

namespace gmt {

/* Vectors Operators: QuadTree=Copy */
QuadNode& QuadNode::operator=(const QuadNode& rhs) { return *this; }

/* Builder Constructor */
QuadNode::QuadNode() {
    this->childs = {nullptr, nullptr, nullptr, nullptr};
    this->corpses = {};
}

/* Default Destructor */
// QuadNode::~QuadNode() {}

bool QuadNode::Leaf() { return !static_cast<bool>(this->childs[0]); }

}  // namespace gmt
#ifndef QuadNode_HPP
#define QuadNode_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Bounds.hpp"
#include "../Geometry/Vector2.hpp"

namespace gmt {

class QuadNode {
   public:
    QuadNode();
    //~QuadNode();
    bool is_leaf();
    std::array<std::unique_ptr<QuadNode>, 4> childs;
    std::vector<std::shared_ptr<phy::Corpse>> corpses;
    QuadNode& operator=(const QuadNode& rhs);
};

}  // namespace gmt

#endif
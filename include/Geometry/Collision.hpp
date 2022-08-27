#ifndef Collision_HPP
#define Collision_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "Bounds.hpp"
#include "Vector2.hpp"
#include "Vertices2.hpp"

namespace gmt {

template <typename T>
class Collision {
   private:
    Collision(phy::Corpse* lhs, phy::Corpse* rhs, gmt::VectorI origin, gmt::VectorI normal);
    phy::Corpse* m_lhs;
    phy::Corpse* m_rhs;

    static std::vector<Collision<T>> circle_on_circle(phy::Circle* circleA, phy::Circle* circleB);
    static std::vector<Collision<T>> circle_on_polygon(phy::Circle* circle, phy::Polygon* polygon);
    static std::vector<Collision<T>> polygon_on_polygon(phy::Polygon* polygonA, phy::Polygon* polygonB);
    static Collision<T> response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal);

   public:
    VectorI origin;  // Collision Origin
    VectorI normal;  // Collision Axis

    static std::vector<Collision<T>> resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs);
};
}  // namespace gmt
#endif
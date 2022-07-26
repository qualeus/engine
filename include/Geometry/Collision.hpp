#ifndef Collision_HPP
#define Collision_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "Bounds.hpp"
#include "Vector.hpp"
#include "Vertices.hpp"

namespace gmt {

template <typename T>
class Collision {
   private:
    Collision(phy::Corpse* lhs, phy::Corpse* rhs, gmt::VectorI origin, gmt::VectorI normal);
    phy::Corpse* lhs;
    phy::Corpse* rhs;

   public:
    VectorI origin;  // Collision Origin
    VectorI normal;  // Collision Axis

    static std::vector<Collision<T>> Resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs);

    static std::vector<Collision<T>> CircleOnCircle(phy::Circle* circleA, phy::Circle* circleB);
    static std::vector<Collision<T>> CircleOnPolygon(phy::Circle* circle, phy::Polygon* polygon);
    static std::vector<Collision<T>> PolygonOnPolygon(phy::Polygon* polygonA, phy::Polygon* polygonB);

    static Collision<T> Response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal);
};
}  // namespace gmt
#endif
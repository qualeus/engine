#ifndef Edge_HPP
#define Edge_HPP

#include <vector>

#include "Config.hpp"
#include "Shape.hpp"

namespace phy {

class Edge : public Shape {
   private:
    // Edge orientation: rightwards normal from A to B
    gmt::VectorI m_point_a;  // first point of the Edge
    gmt::VectorI m_point_b;  // second point of the Edge

    /**
     * @brief Compute moment and centroid. To use when object is initalized or edited
     */
    void calibrate();

   public:
    Edge();
    Edge(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::VectorI point_a, gmt::VectorI point_b);
    Edge& operator=(const Edge& rhs);

    gmt::VectorI get_point_a() const;
    void set_point_a(const gmt::VectorI& point_a);

    gmt::VectorI get_point_b() const;
    void set_point_b(const gmt::VectorI& point_b);

    bool pointed(gmt::VectorI pos) const;
};

}  // namespace phy

#endif
#ifndef Polygon_HPP
#define Polygon_HPP

#include <vector>

#include "Config.hpp"
#include "Shape.hpp"

namespace phy {

class Polygon : public Shape {
   private:
    gmt::VerticesI m_vertices;  // vertices of the polygon (relative to the shape centroid)

    /**
     * @brief Compute moment and centroid. To use when object is initalized or edited
     */
    void calibrate();

   public:
    Polygon();
    Polygon(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::VerticesI vertices);
    Polygon& operator=(const Polygon& rhs);

    gmt::VerticesI get_vertices() const;
    void set_vertices(gmt::VerticesI vertices);

    int get_vertices_number() const;
    void add_vertice(gmt::VectorI point);
    void remove_vertice(int i);

    /**
     * @brief Expensive copy of all the vertices of the ^polygon. Only use it for deep copy and prefer get_vertices() for direct access.
     *
     * @return gmt::VerticesI
     */
    gmt::VerticesI get_copy_vertices() const;

    bool pointed(gmt::VectorI pos) const;
};

}  // namespace phy

#endif
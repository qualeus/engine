#ifndef Circle_HPP
#define Circle_HPP

#include <vector>

#include "Config.hpp"
#include "Shape.hpp"

namespace phy {

class Circle : public Shape {
   private:
    gmt::UnitI m_radius;  // ray of the circle (in m)

    /**
     * @brief Compute moment and centroid. To use when object is initalized or edited
     */
    void calibrate();

   public:
    Circle();
    Circle(gmt::VectorI position, gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::UnitI radius);
    Circle& operator=(const Circle& rhs);

    gmt::UnitI get_radius() const;
    void set_radius(const gmt::UnitI& radius);

    bool pointed(gmt::VectorI pos) const;
};

}  // namespace phy

#endif
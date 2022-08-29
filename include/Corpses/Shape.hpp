#ifndef Shape_HPP
#define Shape_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../Geometry/Geometry.hpp"
#include "Config.hpp"

namespace phy {

class Shape {
   protected:
    gmt::UnitI m_mass;        // mass of the shape (in kg)
    gmt::UnitI m_friction;    // coefficient of friction
    gmt::UnitI m_damping;     // damping ratio
    gmt::UnitI m_moment;      // rotational inertia
    gmt::VectorI m_centroid;  // relative to self points

    /**
     * @brief Compute moment and centroid. To use when object is initalized or edited
     */
    virtual void calibrate() = 0;

   public:
    explicit Shape(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping);

    gmt::UnitI get_mass() const;
    void set_mass(gmt::UnitI mass);

    gmt::UnitI get_friction() const;
    void set_friction(gmt::UnitI friction);

    gmt::UnitI get_damping() const;
    void set_damping(gmt::UnitI damping);

    gmt::UnitI get_moment() const;
    void set_moment(gmt::UnitI moment);

    gmt::VectorI get_centroid() const;
    void set_centroid(gmt::VectorI centroid);

    virtual bool pointed(gmt::VectorI pos) const = 0;
};

}  // namespace phy

#endif
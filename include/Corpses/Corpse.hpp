#ifndef Corpse_HPP
#define Corpse_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../Geometry/Geometry.hpp"
#include "Circle.hpp"
#include "Config.hpp"
#include "Edge.hpp"
#include "Polygon.hpp"
#include "Shape.hpp"

namespace phy {

class Corpse {
   private:
    int m_id;  // unique identifier for retrieval

    bool m_fixed;     // freeze the position / velocity / acceleration
    bool m_tied;      // freeze the rotation / angular velocity / torque
    bool m_etherial;  // bypass every collision with this corpse

    gmt::VectorI m_pos;  // position of the corpse
    gmt::VectorI m_vel;  // velocity of the corpse
    gmt::VectorI m_acc;  // force accumulator

    gmt::UnitI m_rot;  // rotation of the corpse
    gmt::UnitI m_spi;  // angular velocity of the corpse
    gmt::UnitI m_tor;  // torque accumulator

    gmt::UnitI m_mass;    // mass of the shapes
    gmt::UnitI m_moment;  // moment of inertia

    com::vec<com::sptr<Shape>> m_shapes;  // physical geometry

    /**
     * @brief Update the mass and centroid from the shapes data. To use when adding or removing a shape collider in m_shapes.
     */
    void calibrate();

   public:
    explicit Corpse();

    inline bool operator==(const Corpse* other);
    Corpse& operator=(const Corpse& rhs);

    int get_id() const;

    bool get_fixed() const;
    bool get_etherial() const;
    bool get_tied() const;

    void set_fixed(bool fixed);
    void set_etherial(bool etherial);
    void set_tied(bool tied);

    gmt::VectorI get_pos() const;
    gmt::VectorI get_vel() const;
    gmt::VectorI get_acc() const;

    void set_pos(gmt::VectorI pos);
    void set_vel(gmt::VectorI vel);
    void set_acc(gmt::VectorI acc);

    gmt::UnitI get_rot() const;
    gmt::UnitI get_spi() const;
    gmt::UnitI get_tor() const;

    void set_rot(gmt::UnitI rot);
    void set_spi(gmt::UnitI spi);
    void set_tor(gmt::UnitI tor);

    gmt::UnitI get_mass() const;
    gmt::UnitI get_moment() const;

    void add_shape(com::sptr<Shape> shape);
    void remove_shape(int i);
    com::sptr<Shape> get_shape(int i) const;
    com::vec<com::sptr<Shape>> get_shapes() const;
    void set_shapes(com::vec<com::sptr<Shape>> shapes);
    int get_shapes_size() const;

    void apply_force(gmt::VectorI force, gmt::VectorI at);

    gmt::VectorI local_to_global(gmt::VectorI local) const;
    gmt::VectorI global_to_local(gmt::VectorI global) const;

    bool pointed(gmt::VectorI pos) const;

    /**
     * @brief Expensive copy of all the shapes of the body. Only use it for deep copy and prefer get_shapes() for direct access.
     *
     * @return com::vec<com::sptr<phy::Shape>>
     */
    com::vec<com::sptr<Shape>> get_copy_shapes() const;
};

}  // namespace phy

#endif
#ifndef Corpse_HPP
#define Corpse_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../Geometry/Geometry.hpp"
#include "Config.hpp"

namespace phy {

const static int ID_CORPSE = 1;

class Corpse {
   protected:
    int m_id;
    bool m_fixed;
    bool m_tied;
    bool m_etherial;

    gmt::UnitI m_friction;
    gmt::UnitI m_mass;
    gmt::UnitI m_damping;

    gmt::VectorI m_current_pos;
    gmt::VectorI m_last_pos;
    gmt::VectorI m_propulsor;

    gmt::UnitI m_current_rotation;
    gmt::UnitI m_last_rotation;
    gmt::UnitI m_motor;

    gmt::BoundsI m_bounds;

   public:
    explicit Corpse(gmt::UnitI mass, gmt::UnitI damping, bool fixed, bool tied, bool etherial);
    // virtual ~Corpse();
    inline bool operator==(const Corpse* other);
    Corpse& operator=(const Corpse& rhs);

    int get_id() const;
    virtual int get_class() const;
    static int id_class();

    bool get_fixed() const;
    void set_fixed(bool fixed);

    bool get_etherial() const;
    void set_etherial(bool etherial);

    bool get_tied() const;
    void set_tied(bool tied);

    virtual void step() = 0;
    virtual void stop() = 0;
    virtual void bloc() = 0;

    virtual void move(const gmt::VectorI& move) = 0;
    virtual void drag(const gmt::VectorI& drag) = 0;

    virtual void turn(const gmt::UnitI& turn) = 0;
    virtual void rotate(const gmt::UnitI& rotate) = 0;

    virtual bool in_bounds(const gmt::BoundsI& bounds) const = 0;
    virtual bool pointed(const gmt::VectorI& point) const = 0;

    gmt::VectorI get_pos() const;
    gmt::UnitI get_pos_x() const;
    gmt::UnitI get_pos_y() const;

    void set_pos(const gmt::VectorI& pos);
    void set_pos_x(const gmt::UnitI& pos_x);
    void set_pos_y(const gmt::UnitI& pos_y);

    gmt::VectorI get_last_pos() const;
    gmt::UnitI get_last_pos_x() const;
    gmt::UnitI get_last_pos_y() const;

    void set_last_pos(const gmt::VectorI& pos);
    void set_last_pos_x(const gmt::UnitI& pos_x);
    void set_last_pos_y(const gmt::UnitI& pos_y);

    gmt::VectorI get_diff_pos() const;
    gmt::UnitI get_diff_pos_x() const;
    gmt::UnitI get_diff_pos_y() const;

    gmt::VectorI get_propulsor() const;
    void set_propulsor(const gmt::VectorI& propulsor);

    gmt::UnitI get_rotation() const;
    void set_rotation(const gmt::UnitI& current_rotation);
    gmt::UnitI get_diff_rotation() const;

    gmt::UnitI get_last_rotation() const;
    void set_last_rotation(const gmt::UnitI& last_rotation);

    gmt::UnitI get_motor() const;
    void set_motor(const gmt::UnitI& motor);

    void set_damping(const gmt::UnitI& damping);
    gmt::UnitI get_damping() const;
    gmt::UnitI get_bounce() const;

    gmt::UnitI get_mass() const;
    void set_mass(const gmt::UnitI& mass);

    gmt::UnitI get_friction() const;
    void set_friction(const gmt::UnitI& friction);

    gmt::BoundsI get_bounds() const;

    bool equals(const Corpse* other);
};

}  // namespace phy

#endif
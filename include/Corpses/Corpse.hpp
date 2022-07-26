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
    int id;
    bool fixed;
    bool tied;
    bool etherial;

    gmt::UnitI friction;
    gmt::UnitI mass;
    gmt::UnitI damping;

    gmt::VectorI current_pos;
    gmt::VectorI last_pos;
    gmt::VectorI propulsor;

    gmt::UnitI current_rotation;
    gmt::UnitI last_rotation;
    gmt::UnitI motor;

    gmt::BoundsI bounds;

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

    virtual void Step() = 0;
    virtual void Stop() = 0;
    virtual void Bloc() = 0;

    virtual void Move(const gmt::VectorI& move) = 0;
    virtual void Drag(const gmt::VectorI& drag) = 0;

    virtual void Turn(const gmt::UnitI& turn) = 0;
    virtual void Rotate(const gmt::UnitI& rotate) = 0;

    virtual bool inBounds(const gmt::BoundsI& bounds) const = 0;
    virtual bool Pointed(const gmt::VectorI& point) const = 0;

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

    bool Equals(const Corpse* other);
};

}  // namespace phy

#endif
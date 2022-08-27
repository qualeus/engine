#ifndef Contraint_HPP
#define Contraint_HPP

#include "../Common/Maths.hpp"
#include "../Corpses/Circle.hpp"
#include "../Corpses/Corpse.hpp"
#include "../Corpses/Polygon.hpp"
#include "../Geometry/Geometry.hpp"
#include "Config.hpp"

namespace phy {

const static int ID_CONSTRAINT = 1;

class Constraint {
   protected:
    int m_id;

    std::shared_ptr<phy::Corpse> m_corpse_a;
    std::shared_ptr<phy::Corpse> m_corpse_b;

    gmt::VectorI m_relative_pos_a;
    gmt::VectorI m_relative_pos_b;

    bool m_rotation_a;
    bool m_rotation_b;

    gmt::UnitI m_relative_angle_a;
    gmt::UnitI m_relative_angle_b;

    gmt::UnitI m_friction_a;
    gmt::UnitI m_friction_b;

    bool m_breaking;
    bool m_broken;

   public:
    explicit Constraint(std::shared_ptr<phy::Corpse> corpse_a,
                        std::shared_ptr<phy::Corpse> corpse_b,
                        gmt::VectorI relative_pos_a,
                        gmt::VectorI relative_pos_b,
                        gmt::UnitI relative_angle_a,
                        gmt::UnitI relative_angle_b,
                        bool rotation_a,
                        bool rotation_b,
                        gmt::UnitI friction_a,
                        gmt::UnitI friction_b,
                        bool breaking);

    inline bool operator==(const Constraint* other);
    Constraint& operator=(const Constraint& rhs);

    int get_id() const;
    virtual int get_class() const;
    static int id_class();

    virtual void step() = 0;

    bool equals(const Constraint* other) const;

    std::shared_ptr<phy::Corpse> get_corpse_a() const;
    void set_corpse_a(std::shared_ptr<phy::Corpse> corpse_a);

    std::shared_ptr<phy::Corpse> get_corpse_b() const;
    void set_corpse_b(std::shared_ptr<phy::Corpse> corpse_b);

    gmt::VectorI get_relative_pos_a() const;
    void set_relative_pos_a(gmt::VectorI relative_pos_a);

    gmt::VectorI get_relative_pos_b() const;
    void set_relative_pos_b(gmt::VectorI relative_pos_b);

    bool get_rotation_a() const;
    void set_rotation_a(bool rotation_a);

    bool get_rotation_b() const;
    void set_rotation_b(bool rotation_b);

    gmt::UnitI get_relative_angle_a() const;
    void set_relative_angle_a(gmt::UnitI angle_a);

    gmt::UnitI get_relative_angle_b() const;
    void set_relative_angle_b(gmt::UnitI angle_b);

    gmt::UnitI get_friction_a() const;
    void set_friction_a(gmt::UnitI friction_a);

    gmt::UnitI get_friction_b() const;
    void set_friction_b(gmt::UnitI friction_b);

    bool get_breaking() const;
    void set_breaking(bool breaking);

    bool get_broken() const;
    void set_broken(bool broken);
};
}  // namespace phy

#endif
#ifndef Circle_HPP
#define Circle_HPP

#include <vector>

#include "Config.hpp"
#include "Corpse.hpp"
#include "Polygon.hpp"

namespace phy {

const static int ID_CIRCLE = 2;

class Circle : public Corpse {
   private:
    gmt::UnitI m_size;

   public:
    Circle(gmt::UnitI x = gmt::UnitI(0),
           gmt::UnitI y = gmt::UnitI(0),
           gmt::UnitI size = gmt::UnitI(1),
           gmt::UnitI mass = gmt::UnitI(1),
           gmt::UnitI damping = gmt::UnitI(1),
           gmt::UnitI speed_x = gmt::UnitI(0),
           gmt::UnitI speed_y = gmt::UnitI(0),
           gmt::UnitI rotation = gmt::UnitI(0),
           gmt::UnitI motor = gmt::UnitI(0),
           bool fixed = false,
           bool tied = false,
           bool etherial = false);

    // virtual ~Circle();

    Circle& operator=(const Circle& rhs);

    int get_class() const;
    static int id_class();

    void step();
    void stop();
    void bloc();

    void move(const gmt::VectorI& move);
    void drag(const gmt::VectorI& drag);

    void turn(const gmt::UnitI& turn);
    void rotate(const gmt::UnitI& rotate);

    bool in_bounds(const gmt::BoundsI& bounds) const;
    bool pointed(const gmt::VectorI& point) const;

    void update_bounds();
    gmt::UnitI get_size() const;
    void set_size(const gmt::UnitI& size);
};

}  // namespace phy

#endif
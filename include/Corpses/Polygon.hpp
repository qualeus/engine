#ifndef Polygon_HPP
#define Polygon_HPP

#include <vector>

#include "Circle.hpp"
#include "Config.hpp"
#include "Corpse.hpp"

namespace phy {

const static int ID_POLYGON = 3;

class Polygon : public Corpse {
   private:
    gmt::VerticesI m_points;
    std::vector<gmt::VerticesI> m_polygons;

   public:
    Polygon(std::vector<gmt::VectorI> points = {},
            gmt::UnitI mass = gmt::UnitI(1),
            gmt::UnitI damping = gmt::UnitI(1),
            gmt::UnitI speed_x = gmt::UnitI(0),
            gmt::UnitI speed_y = gmt::UnitI(0),
            gmt::UnitI rotation = gmt::UnitI(0),
            gmt::UnitI motor = gmt::UnitI(0),
            bool fixed = false,
            bool tied = false,
            bool etherial = false);

    Polygon& operator=(const Polygon& rhs);

    // virtual ~Polygon();

    const int get_class();

    static int id_class();

    void step();

    void stop();

    void bloc();

    void move(const gmt::VectorI& move);
    void drag(const gmt::VectorI& drag);

    void turn(const gmt::UnitI& move);
    void rotate(const gmt::UnitI& rotate);

    bool in_bounds(const gmt::BoundsI& bounds) const;
    bool pointed(const gmt::VectorI& point) const;

    void generate();

    int get_points_number() const;
    void add_point(gmt::VectorI point);
    void remove_point(int i);

    gmt::VerticesI get_points() const;
    void set_points(gmt::VerticesI points);
    int get_points_size() const;

    std::vector<gmt::VerticesI> get_polygons() const;
    void set_polygons(std::vector<gmt::VerticesI> polygons);
    int get_polygons_size() const;

    void update_bounds();

    std::vector<std::pair<std::shared_ptr<gmt::VectorI>, std::shared_ptr<gmt::VectorI>>> get_sides() const;
};

}  // namespace phy

#endif
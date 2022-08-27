#include "../../include/Corpses/Polygon.hpp"

namespace phy {

Polygon::Polygon(std::vector<gmt::VectorI> points,
                 gmt::UnitI mass,
                 gmt::UnitI damping,
                 gmt::UnitI speed_x,
                 gmt::UnitI speed_y,
                 gmt::UnitI rotation,
                 gmt::UnitI motor,
                 bool fixed,
                 bool tied,
                 bool etherial)
    : Corpse(mass, damping, fixed, tied, etherial) {
    std::vector<std::shared_ptr<gmt::VectorI>> shared_points = {};
    for (int i = 0; i < points.size(); i++) { shared_points.push_back(std::make_shared<gmt::VectorI>(points[i])); }

    m_points = gmt::VerticesI(shared_points);

    generate();

    gmt::VectorI centroid = m_points.centroid();

    m_current_pos = centroid;
    m_last_pos = gmt::VectorI(centroid.x - speed_x, centroid.y - speed_y);

    m_current_rotation = gmt::UnitI(0);
    m_last_rotation = rotation;

    m_motor = motor;

    m_bounds = m_points.limits();
}
Polygon& Polygon::operator=(const Polygon& rhs) {
    Corpse::operator=(rhs);
    gmt::VerticesI rpoints = rhs.get_points();
    m_points = gmt::VerticesI();
    for (int i = 0; i < rpoints.vertices.size(); i++) { m_points.vertices.push_back(std::make_shared<gmt::VectorI>(*rpoints.vertices[i])); }
    generate();
    return *this;
}
// Polygon::~Polygon() {}

const int Polygon::get_class() {
    return ID_POLYGON;
}
int Polygon::id_class() {
    return ID_POLYGON;
}

void Polygon::move(const gmt::VectorI& move) {
    m_points.translate(move - m_current_pos);
    m_current_pos = move;
}
void Polygon::drag(const gmt::VectorI& drag) {
    m_points.translate(drag);
    m_current_pos = m_current_pos + drag;
}

void Polygon::turn(const gmt::UnitI& turn) {
    m_points.rotate(m_current_rotation - turn, m_current_pos);
    m_current_rotation = std::fmod(turn, gmt::UnitI(RO));
}
void Polygon::rotate(const gmt::UnitI& rotate) {
    m_points.rotate(rotate, m_current_pos);
    m_current_rotation = std::fmod(m_current_rotation + rotate, gmt::UnitI(RO));
}

bool Polygon::in_bounds(const gmt::BoundsI& bounds) const {
    return gmt::BoundsI::bounds_in_bounds(get_bounds(), bounds);
}
bool Polygon::pointed(const gmt::VectorI& point) const {
    return gmt::VerticesI::point_in_shape(get_points(), point);
}

void Polygon::add_point(gmt::VectorI point) {
    m_points.vertices.push_back(std::make_shared<gmt::VectorI>(point));

    generate();

    gmt::VectorI computed_center = m_points.centroid();
    gmt::VectorI diff_pos = computed_center - m_current_pos;

    m_current_pos = computed_center;
    m_last_pos = m_last_pos + diff_pos;
}

void Polygon::remove_point(int i) {
    m_points.vertices.erase(std::begin(m_points.vertices) + com::modulo(i + 1, m_points.vertices.size()));

    generate();

    gmt::VectorI computed_center = m_points.centroid();
    gmt::VectorI diff_pos = computed_center - m_current_pos;

    m_current_pos = computed_center;
    m_last_pos = m_last_pos + diff_pos;
}

void Polygon::step() {
    if (m_fixed) {
        m_last_pos = m_current_pos;
    } else {
        gmt::VectorI diff_pos = m_current_pos - m_last_pos;
        m_last_pos = m_current_pos;
        drag(diff_pos);
    }

    if (m_tied) {
        m_last_rotation = std::fmod(m_current_rotation, gmt::UnitI(RO));
    } else {
        gmt::UnitI diff_rotation = m_current_rotation - m_last_rotation;
        m_last_rotation = m_current_rotation;
        rotate(diff_rotation);
    }

    // Update bounds
    update_bounds();
    // Add the motor rotation even if the object is tied
    // if (!gmt::decimal_equals(motor, 0.0f, 0.0001f)) { m_current_rotation = m_current_rotation + motor; }
}
void Polygon::update_bounds() {
    m_bounds = m_points.limits();
}
void Polygon::stop() {
    m_last_pos = m_current_pos;
}
void Polygon::bloc() {
    m_last_rotation = m_current_rotation;
}

void Polygon::generate() {
    // Put the vertex in the Counter Clockwise order
    m_points.reorder();

    if (m_points.convex()) {
        m_polygons = {m_points};  // Convex => Collision shape is the same
    } else {
        if (m_points.intersect()) {
            // If the polygon is self-intersecting, we redefine the shape
            gmt::VerticesI hull = m_points.hull();
            m_polygons = {hull};
            m_points = hull;
        } else {
            // Else we can just triangulate it
            m_polygons = m_points.triangulate();
        }
    }
}

gmt::VerticesI Polygon::get_points() const {
    return m_points;
}

void Polygon::set_points(gmt::VerticesI points) {
    m_points = points;
}

int Polygon::get_points_size() const {
    return m_points.vertices.size();
}

std::vector<gmt::VerticesI> Polygon::get_polygons() const {
    return m_polygons;
}

void Polygon::set_polygons(std::vector<gmt::VerticesI> polygons) {
    m_polygons = polygons;
}

int Polygon::get_polygons_size() const {
    return m_polygons.size();
}

std::vector<std::pair<std::shared_ptr<gmt::VectorI>, std::shared_ptr<gmt::VectorI>>> Polygon::get_sides() const {
    return m_points.pairs();
}

}  // namespace phy

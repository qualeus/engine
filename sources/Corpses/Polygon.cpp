#include "../../include/Corpses/Polygon.hpp"

namespace phy {

Polygon::Polygon() : Shape(gmt::UnitI(), gmt::UnitI(), gmt::UnitI()) {
    m_vertices = {};

    calibrate();
}

Polygon::Polygon(gmt::UnitI mass, gmt::UnitI friction, gmt::UnitI damping, gmt::VerticesI vertices) : Shape(mass, friction, damping) {
    m_vertices = vertices;

    calibrate();
}

Polygon& Polygon::operator=(const Polygon& rhs) {
    Shape::operator=(rhs);

    // copy the other polygon vertices
    gmt::VerticesI copy_vertices = rhs.get_copy_vertices();

    m_vertices = copy_vertices;

    return *this;
}

// Vertices getters
gmt::VerticesI Polygon::get_vertices() const {
    return m_vertices;
}

// Vertices setters
void Polygon::set_vertices(gmt::VerticesI vertices) {
    m_vertices = vertices;
}
void Polygon::add_vertice(gmt::VectorI point) {
    m_vertices.vertices.push_back(point);
}
void Polygon::remove_vertice(int i) {
    com::remove(i, m_vertices.vertices);  // remove ordered to keep edges coherence
}

gmt::VerticesI Polygon::get_copy_vertices() const {
    gmt::VerticesI copy_vertices = gmt::VerticesI();

    for (int i = 0; i < m_vertices.vertices.size(); ++i) {
        gmt::VectorI copy_vertice = m_vertices.vertices[i];

        copy_vertices.vertices.push_back(copy_vertice);
    }

    return copy_vertices;
}

void Polygon::calibrate() {
    gmt::VectorI temp_centroid = m_vertices.centroid();  // centered origin

    // Update vertices for the new centroid
    gmt::VectorI diff_centroid = temp_centroid - m_centroid;
    for (int i = 0; i < m_vertices.vertices.size(); ++i) { m_vertices.vertices[i] += diff_centroid; }
    m_centroid = temp_centroid;

    com::vec<gmt::VerticesI> triangles = m_vertices.triangulate();  // triangulate

    for (int i = 0; i < triangles.size(); i++) {
        // TODO: https://fotino.me/moment-of-inertia-algorithm/
    }

    m_moment = gmt::UnitI();
}

bool Polygon::pointed(gmt::VectorI pos) const {
    return false;  // TODO
}

}  // namespace phy

#include "../../include/Geometry/Collision.hpp"

namespace gmt {

template <typename T>
Collision<T>::Collision(phy::Corpse* _lhs, phy::Corpse* _rhs, gmt::VectorI _origin, gmt::VectorI _normal) {
    m_lhs = _lhs;
    m_rhs = _rhs;
    origin = _origin;
    normal = _normal;
}
template Collision<int>::Collision(phy::Corpse* lhs, phy::Corpse* rhs, gmt::VectorI origin, gmt::VectorI normal);
template Collision<float>::Collision(phy::Corpse* lhs, phy::Corpse* rhs, gmt::VectorI origin, gmt::VectorI normal);
template Collision<double>::Collision(phy::Corpse* lhs, phy::Corpse* rhs, gmt::VectorI origin, gmt::VectorI normal);

template <typename T>
std::vector<Collision<T>> Collision<T>::resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs) {
    /* Left Hand Side pointer classes */
    phy::Circle* lcircle = nullptr;
    phy::Polygon* lpolygon = nullptr;

    /* Right Hand Side pointer classes */
    phy::Circle* rcircle = nullptr;
    phy::Polygon* rpolygon = nullptr;

    /* Id classes */
    int lhs_class = -1;
    int rhs_class = -1;

    if (lcircle = dynamic_cast<phy::Circle*>(lhs.get())) {
        lhs_class = lcircle->get_class();
    } else if (lpolygon = dynamic_cast<phy::Polygon*>(lhs.get())) {
        lhs_class = lpolygon->get_class();
    }

    if (rcircle = dynamic_cast<phy::Circle*>(rhs.get())) {
        rhs_class = rcircle->get_class();
    } else if (rpolygon = dynamic_cast<phy::Polygon*>(rhs.get())) {
        rhs_class = rpolygon->get_class();
    }

    /* Possible to factorise but it's easier to read like that */
    if (lhs_class == phy::Circle::id_class() && rhs_class == phy::Circle::id_class()) {
        return Collision<T>::circle_on_circle(rcircle, lcircle);
    } else if (lhs_class == phy::Circle::id_class() && rhs_class == phy::Polygon::id_class()) {
        return Collision<T>::circle_on_polygon(lcircle, rpolygon);
    } else if (lhs_class == phy::Polygon::id_class() && rhs_class == phy::Circle::id_class()) {
        return Collision<T>::circle_on_polygon(rcircle, lpolygon);
    } else if (lhs_class == phy::Polygon::id_class() && rhs_class == phy::Polygon::id_class()) {
        return Collision<T>::polygon_on_polygon(rpolygon, lpolygon);
    }

    /* If can't resolve corpses */
    return {};  // Return no collision
}
template std::vector<Collision<int>> Collision<int>::resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs);
template std::vector<Collision<float>> Collision<float>::resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs);
template std::vector<Collision<double>> Collision<double>::resolve(std::shared_ptr<phy::Corpse> lhs, std::shared_ptr<phy::Corpse> rhs);

/* Circle / Circle Collision */
template <typename T>
std::vector<Collision<T>> Collision<T>::circle_on_circle(phy::Circle* circleA, phy::Circle* circleB) {
    UnitI distance = gmt::VectorI::distance(circleA->get_pos(), circleB->get_pos()) + gmt::UnitI(1);
    UnitI overlap = (circleA->get_size() + circleB->get_size()) - distance;

    if (overlap < 0) { return {}; }  // Not colliding

    UnitI x_diff = circleA->get_pos_x() - circleB->get_pos_x();
    UnitI y_diff = circleA->get_pos_y() - circleB->get_pos_y();

    VectorI vector_response = gmt::VectorI(x_diff / distance, y_diff / distance) * overlap;
    VectorI vector_origin = circleA->get_pos() - vector_response.normalize() * circleA->get_size();
    return {Collision<T>::response(circleA, circleB, vector_origin, vector_response)};
}
template std::vector<Collision<int>> Collision<int>::circle_on_circle(phy::Circle* circleA, phy::Circle* circleB);
template std::vector<Collision<float>> Collision<float>::circle_on_circle(phy::Circle* circleA, phy::Circle* circleB);
template std::vector<Collision<double>> Collision<double>::circle_on_circle(phy::Circle* circleA, phy::Circle* circleB);

/* Circle / Polygon collision */
template <typename T>
std::vector<Collision<T>> Collision<T>::circle_on_polygon(phy::Circle* circle, phy::Polygon* polygon) {
    // Collide if the center of the circle is in the polygon
    /*
    if (polygon->Pointed(gmt::VectorI(circle->get_pos()))) {
        std::pair<std::shared_ptr<gmt::VectorI>, std::shared_ptr<gmt::VectorI>> closest_edge = gmt::VerticesI::closest_edge(polygon->get_points(), circle->get_pos());

        gmt::VectorI closest_projection = gmt::VectorI::segment_projection(*closest_edge.first, *closest_edge.second, circle->get_pos());
        gmt::VectorI vector_response = (gmt::VectorI::normal(*closest_edge.second, *closest_edge.first)).normalize() * (gmt::VectorI::Distance(circle->get_pos(), closest_projection) +
    circle->get_size()); VectorI vector_origin = (*closest_edge.first + *closest_edge.second) / T(2);

        return {Collision<T>::Response(polygon, circle, vector_origin, vector_response)};
    }*/

    const std::vector<gmt::VerticesI> triangles = polygon->get_polygons();

    std::vector<Collision<T>> collisions = {};

    for (int i = 0; i < triangles.size(); i++) {
        gmt::VerticesI triangle = triangles[i];

        // Collide if the center of the circle is in the polygon
        if (gmt::VerticesI::point_in_shape(triangle, gmt::VectorI(circle->get_pos()))) {
            std::pair<std::shared_ptr<gmt::VectorI>, std::shared_ptr<gmt::VectorI>> closest_edge = gmt::VerticesI::closest_edge(triangle, circle->get_pos());

            gmt::VectorI closest_projection = gmt::VectorI::segment_projection(*closest_edge.first, *closest_edge.second, circle->get_pos());
            gmt::VectorI vector_response =
                (gmt::VectorI::normal(*closest_edge.second, *closest_edge.first)).normalize() * (gmt::VectorI::distance(circle->get_pos(), closest_projection) + circle->get_size());
            VectorI vector_origin = (*closest_edge.first + *closest_edge.second) / T(2);

            return {Collision<T>::response(polygon, circle, vector_origin, vector_response)};
        }

        std::vector<std::pair<std::shared_ptr<gmt::VectorI>, std::shared_ptr<gmt::VectorI>>> pairs = triangle.pairs();
        // Collide if one side of the polygon intersect with the circle
        for (int i = 0; i < pairs.size(); i++) {
            std::pair<int, gmt::VectorI> test_intersect = gmt::VectorI::line_cercle_intersect(*pairs[i].first, *pairs[i].second, circle->get_pos(), circle->get_size());

            // Don't collide with any edge
            if (test_intersect.first == 0) { continue; }

            if (test_intersect.first == 1) {
                // Collide at the middle of an edge
                gmt::VectorI vector_response = (circle->get_pos() - test_intersect.second).normalize() * (gmt::VectorI::distance(circle->get_pos(), test_intersect.second) - circle->get_size());
                collisions.push_back(Collision<T>::response(polygon, circle, test_intersect.second, vector_response));
                break;

            } else if (test_intersect.first == 2) {
                // Collide with the first point of the edge (current edge + last edge)
                int last_edge = com::modulo(i - 1, pairs.size());
                gmt::VectorI normals_average =
                    gmt::VectorI::normal(*pairs[last_edge].first, *pairs[last_edge].second).normalize() + gmt::VectorI::normal(*pairs[i].first, *pairs[i].second).normalize();
                gmt::VectorI vector_response = normals_average.normalize() * (gmt::VectorI::distance(circle->get_pos(), *pairs[i].first) - circle->get_size());

                collisions.push_back(Collision<T>::response(polygon, circle, test_intersect.second, -vector_response));
                break;

            } else if (test_intersect.first == 3) {
                // Collide with the second point of the edge (current edge + next edge)
                int next_edge = com::modulo(i + 1, pairs.size());
                gmt::VectorI normals_average =
                    gmt::VectorI::normal(*pairs[i].first, *pairs[i].second).normalize() + gmt::VectorI::normal(*pairs[next_edge].first, *pairs[next_edge].second).normalize();
                gmt::VectorI vector_response = normals_average.normalize() * (gmt::VectorI::distance(circle->get_pos(), *pairs[i].second) - circle->get_size());
                collisions.push_back(Collision<T>::response(polygon, circle, test_intersect.second, -vector_response));
                break;
            }
        }
    }
    if (collisions.size() > 0) { return collisions; }

    /* If no collision occured */
    return {};  // Not colliding
}

template std::vector<Collision<int>> Collision<int>::circle_on_polygon(phy::Circle* circle, phy::Polygon* polygon);
template std::vector<Collision<float>> Collision<float>::circle_on_polygon(phy::Circle* circle, phy::Polygon* polygon);
template std::vector<Collision<double>> Collision<double>::circle_on_polygon(phy::Circle* circle, phy::Polygon* polygon);

/* Polygon / Polygon collision */
template <typename T>
std::vector<Collision<T>> Collision<T>::polygon_on_polygon(phy::Polygon* polygonA, phy::Polygon* polygonB) {
    // SAT algorithm
    const std::vector<gmt::VerticesI> trianglesA = polygonA->get_polygons();
    const std::vector<gmt::VerticesI> trianglesB = polygonB->get_polygons();

    std::vector<Collision<T>> collisions = {};

    for (int a = 0; a < trianglesA.size(); a++) {
        gmt::VerticesI triangleA = trianglesA[a];

        // Compute the normals of the Sub-PolygonA
        std::vector<VectorI> normalsA = {};
        for (int i = 0; i < triangleA.vertices.size(); i++) { normalsA.push_back(VectorI::normal(*triangleA.vertices[i])); }

        for (int b = 0; b < trianglesB.size(); b++) {
            gmt::VerticesI triangleB = trianglesB[b];

            // Add the normals of the Sub-PolygonB
            std::vector<VectorI> normalsAB = normalsA;
            for (int i = 0; i < triangleB.vertices.size(); i++) { normalsAB.push_back(VectorI::normal(*triangleB.vertices[i])); }

            // Check if the intervals overlap
            for (int i = 0; i < normalsAB.size(); i++) {
                VectorI normal = normalsAB[i];

                std::vector<UnitI> dotsA = {};
                std::vector<UnitI> dotsB = {};

                for (int j = 0; j < triangleA.vertices.size(); j++) { dotsA.push_back(VectorI::dot(*triangleA.vertices[j], normal)); }
                for (int j = 0; j < triangleB.vertices.size(); j++) { dotsB.push_back(VectorI::dot(*triangleB.vertices[j], normal)); }

                const auto minmax_A = std::minmax_element(dotsA.begin(), dotsA.end());
                const auto minmax_B = std::minmax_element(dotsB.begin(), dotsB.end());

                UnitI min_A = *minmax_A.first;
                UnitI max_A = *minmax_A.second;
                UnitI min_B = *minmax_B.first;
                UnitI max_B = *minmax_B.second;

                if (min_A < max_B && min_A > min_B) { continue; }
                if (min_B < max_A && min_B > min_A) { continue; }
                return {};  // Not colliding
            }

            // A collision is occuring
            VectorI centroidA = triangleA.centroid();
            VectorI centroidB = triangleB.centroid();

            // Compute the normal between the two shapes
            VectorI normal = VectorI::normal(centroidB - centroidA);

            // Project the points of each shape the normal
            std::vector<UnitI> dotsA = {};
            std::vector<UnitI> dotsB = {};

            // Determine the forward hull min and max index
            for (int j = 0; j < triangleA.vertices.size(); j++) { dotsA.push_back(VectorI::dot(*triangleA.vertices[j], normal)); }
            for (int j = 0; j < triangleB.vertices.size(); j++) { dotsB.push_back(VectorI::dot(*triangleB.vertices[j], normal)); }

            const auto minmax_A = std::minmax_element(dotsA.begin(), dotsA.end());
            const auto minmax_B = std::minmax_element(dotsB.begin(), dotsB.end());

            UnitI min_idA = std::distance(dotsA.begin(), minmax_A.first);
            UnitI max_idA = std::distance(dotsA.begin(), minmax_A.second);
            UnitI min_idB = std::distance(dotsB.begin(), minmax_B.first);
            UnitI max_idB = std::distance(dotsB.begin(), minmax_B.second);

            // For each point of both hull, project it on each edge of the other polygon and find the minimum distance
            UnitI min_dist = UnitI(1000000);
            VectorI collision_origin = VectorI();
            VectorI collision_normal = VectorI();

            std::vector<int> fwdhull_A = com::cyclic_indexes(max_idA, min_idA, dotsA.size());
            std::vector<int> fwdhull_B = com::cyclic_indexes(min_idB, max_idB, dotsB.size());

            // Projection of the shape A
            for (int i = 0; i < fwdhull_A.size(); i++) {
                VectorI vectA = *triangleA.vertices[fwdhull_A[i]];

                for (int i = 0; i < fwdhull_B.size() - 1; i++) {
                    VectorI vectB1 = *triangleB.vertices[fwdhull_B[i]];
                    VectorI vectB2 = *triangleB.vertices[fwdhull_B[i + 1]];
                    VectorI vectB = VectorI::segment_projection(vectA, vectB1, vectB2);
                    if (VectorI::point_on_segment(vectB1, vectB2, vectA)) {
                        UnitI dist = VectorI::distance(vectA, vectB);
                        if (dist < min_dist) {
                            min_dist = dist;
                            collision_origin = vectB;
                            collision_normal = vectA - vectB;
                        }
                    }
                }
            }

            // Projection of the shape B
            for (int i = 0; i < fwdhull_B.size(); i++) {
                VectorI vectB = *triangleB.vertices[fwdhull_B[i]];

                for (int i = 0; i < fwdhull_A.size() - 1; i++) {
                    VectorI vectA1 = *triangleA.vertices[fwdhull_A[i]];
                    VectorI vectA2 = *triangleA.vertices[fwdhull_A[i + 1]];
                    VectorI vectA = VectorI::segment_projection(vectB, vectA1, vectA2);
                    if (VectorI::point_on_segment(vectA1, vectA2, vectB)) {
                        UnitI dist = VectorI::distance(vectB, vectA);
                        if (dist < min_dist) {
                            min_dist = dist;
                            collision_origin = vectA;
                            collision_normal = vectA - vectB;
                        }
                    }
                }
            }

            collisions.push_back(Collision<T>::response(polygonA, polygonB, collision_origin, collision_normal));
        }
    }
    return collisions;
}
template std::vector<Collision<int>> Collision<int>::polygon_on_polygon(phy::Polygon* polygonA, phy::Polygon* polygonB);
template std::vector<Collision<float>> Collision<float>::polygon_on_polygon(phy::Polygon* polygonA, phy::Polygon* polygonB);
template std::vector<Collision<double>> Collision<double>::polygon_on_polygon(phy::Polygon* polygonA, phy::Polygon* polygonB);

template <typename T>
Collision<T> Collision<T>::response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal) {
    gmt::UnitI damping = (lhs->get_bounce() + rhs->get_bounce()) / gmt::UnitI(2);  // Damping is evenly distributed among the corpses

    /*
        TEMP: TODO
        - recompute the damping with the proper forces applied
        - push the corpse out of the other shape with the normal vector and the force passed by parameter (vect_force)
            => BUT DON'T CHANCE THE VELOCITY (how to do? last pos?)
        - Then apply the vector (2m2v¯2 + (m1 −m2)v¯1)/(2m2v¯2 + (m1 −m2)v¯1)

    */
    // Test if the collision is asymetric (Fixed/Not Fixed) / or if the two corpses are Fixed
    if (lhs->get_fixed() || rhs->get_fixed()) {
        if (!lhs->get_fixed()) {
            // corpse_a is Not Fixed and corpse_b is Fixed:
            // gmt::VectorI temp_pos = corpse_a->get_last_pos();

            // corpse_a->set_last_pos(corpse_a->get_pos());
            lhs->drag(normal);
            // corpse_a->Move(gmt::Mirrored_Point(temp_pos - corpse_a->get_pos(), vect_force) * damping);

        } else if (!rhs->get_fixed()) {
            // corpse_a is Fixed and corpse_b is Not Fixed:
            // gmt::VectorI temp_pos = corpse_b->get_last_pos();

            // corpse_b->set_last_pos(corpse_b->get_pos());
            rhs->drag(-normal);
            // corpse_b->Move(gmt::Mirrored_Point(temp_pos - corpse_b->get_pos(), vect_force) * damping);
        } else {
            // Both corpse_a and corpse_b are Fixed:
            // corpse_a->Move(force*0.5f);
            // corpse_b->Move(-force*0.5f);
        }
    } else {
        // Both corpse_a and corpse_b are Not Fixed:
        gmt::UnitI normal_mass = lhs->get_mass() + rhs->get_mass();
        gmt::UnitI normal_mass_corpse_a = lhs->get_mass() / normal_mass;
        gmt::UnitI normal_mass_corpse_b = rhs->get_mass() / normal_mass;

        // gmt::VectorI diff_pos_a = corpse_a->get_diff_pos();
        // gmt::VectorI diff_pos_b = corpse_b->get_diff_pos();

        // corpse_a->set_last_pos(corpse_a->get_pos());
        // corpse_b->set_last_pos(corpse_b->get_pos());

        lhs->drag(normal * normal_mass_corpse_b / gmt::UnitI(2));
        rhs->drag(-normal * normal_mass_corpse_a / gmt::UnitI(2));
        /*
        // Distance between corpses
        gmt::UnitI fDistance = gmt::Length(corpse_a->get_pos_x(), corpse_a->get_pos_y(), corpse_b->get_pos_x(), corpse_b->get_pos_y());

        // Normal
        gmt::UnitI nx = (corpse_b->get_pos_x() - corpse_a->get_pos_x()) / fDistance;
        gmt::UnitI ny = (corpse_b->get_pos_y() - corpse_a->get_pos_y()) / fDistance;

        // Tangent
        gmt::UnitI tx = -nx;
        gmt::UnitI ty = ny;

        // Dot product Tangent
        gmt::UnitI dpTanA = diff_pos_a.x * tx + diff_pos_a.y * ty;
        gmt::UnitI dpTanB = diff_pos_b.x * tx + diff_pos_b.y * ty;

        // Dot product Normal
        gmt::UnitI dpNormA = diff_pos_a.x * nx + diff_pos_a.y * ny;
        gmt::UnitI dpNormB = diff_pos_b.x * nx + diff_pos_b.y * ny;

        // Conservation of momentum
        gmt::UnitI mA = (dpNormA * (corpse_a->get_mass() - corpse_b->get_mass()) + 2.0f * corpse_b->get_mass() * dpNormB) / (corpse_a->get_mass() + corpse_b->get_mass());
        gmt::UnitI mB = (dpNormB * (corpse_b->get_mass() - corpse_a->get_mass()) + 2.0f * corpse_a->get_mass() * dpNormA) / (corpse_a->get_mass() + corpse_b->get_mass());

        corpse_a->Move(tx * dpTanA + nx * mA, ty * dpTanA + ny * mA);
        corpse_b->Move(tx * dpTanB + nx * mB, ty * dpTanB + ny * mB);
        */

        // corpse_a->Move(gmt::Mirrored_Point(temp_pos_a - corpse_a->get_pos(), vect_force) * damping);
        // corpse_b->Move(gmt::Mirrored_Point(temp_pos_b - corpse_b->get_pos(), vect_force) * damping);
    }

    return Collision<T>(lhs, rhs, origin, normal);
}

template Collision<int> Collision<int>::response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal);
template Collision<float> Collision<float>::response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal);
template Collision<double> Collision<double>::response(phy::Corpse* lhs, phy::Corpse* rhs, const VectorI& origin, const VectorI& normal);

}  // namespace gmt
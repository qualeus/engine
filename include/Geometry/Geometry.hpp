#ifndef Geometry_HPP
#define Geometry_HPP

#include "../Benchmark/Recorder.hpp"
#include "../Common/Maths.hpp"
#include "Bounds.hpp"
#include "Config.hpp"
#include "Vector2.hpp"
#include "Vertices2.hpp"

namespace gmt {

#ifndef PRECISION_SET
#define PRECISION_SET
typedef float QUALEUS_PRECISION;
#endif

#define MIN_DAMPING 0.001
#define MAX_DAMPING 100
#define MAX_GRAVITY_DISTANCE 1000000000 /* To avoid strange behaviours when comparing big numbers */

using UnitI = QUALEUS_PRECISION;
using VectorI = Vector2<QUALEUS_PRECISION>;
using BoundsI = Bounds<QUALEUS_PRECISION>;
using VerticesI = Vertices2<QUALEUS_PRECISION>;
using CollisionI = Collision<QUALEUS_PRECISION>;

}  // namespace gmt
#endif
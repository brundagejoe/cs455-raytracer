#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include "color.hpp"
#include "point3d.hpp"
#include "vector.hpp"

struct HitRecord {
    Point3D point;
    Color color;
    Vector normal;
    double distanceFromOrigin;
};

#endif  // HIT_RECORD_HPP
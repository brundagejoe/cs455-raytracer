#include "point3d.hpp"

Point3D interpolatePoint(const Point3D& a, const Point3D& b, const double t) {
    if (t < 0 || t > 1) {
        throw std::invalid_argument("t must be between 0 and 1");
    }

    return a * (1 - t) + b * t;
}

Point3D interpolatePoints(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d, const double u, const double v) {
    return interpolatePoint(interpolatePoint(a, b, u), interpolatePoint(c, d, u), v);
}

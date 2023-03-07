#include "triplet.hpp"
#include "vector.hpp"

#ifndef POINT3D_HPP
#define POINT3D_HPP

class Point3D : public Triplet {
   public:
    Point3D() = default;
    Point3D(const Triplet& t) : Triplet(t){};
    Point3D(const double x, const double y, const double z) : Triplet(x, y, z){};
    ~Point3D() = default;

    Point3D rotateX(const double angle) const {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        return Point3D(x, y * cosAngle - z * sinAngle, y * sinAngle + z * cosAngle);
    }
    Point3D rotateY(const double angle) const {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        return Point3D(x * cosAngle + z * sinAngle, y, -x * sinAngle + z * cosAngle);
    }
    Point3D rotateZ(const double angle) const {
        double cosAngle = cos(angle);
        double sinAngle = sin(angle);
        return Point3D(x * cosAngle - y * sinAngle, x * sinAngle + y * cosAngle, z);
    }
};

inline Vector operator-(const Point3D& a, const Point3D& b) {
    return Vector(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

Point3D interpolatePoint(const Point3D& a, const Point3D& b, const double t);
Point3D interpolatePoints(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d, const double t, const double u);

#endif  // POINT3D_HPP
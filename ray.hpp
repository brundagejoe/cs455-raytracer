#include "point3d.hpp"
#include "vector.hpp"

#ifndef RAY_HPP
#define RAY_HPP

class Ray {
   private:
    Point3D origin;
    Vector direction;

   public:
    Ray() = default;
    Ray(const Point3D& origin, const Vector& direction)
        : origin(origin), direction(direction) {}
    ~Ray() = default;

    Point3D getOrigin() const { return origin; }
    Vector getDirection() const { return direction; }
    Point3D at(double t) const { return origin + t * direction; }
};

inline bool operator==(const Ray& lhs, const Ray& rhs) {
    return lhs.getOrigin() == rhs.getOrigin() &&
           lhs.getDirection() == rhs.getDirection();
}

#endif  // RAY_HPP
#include <cmath>

#include "triplet.hpp"

#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector : public Triplet {
   public:
    Vector() = default;
    Vector(const Triplet& t) : Triplet(t){};
    Vector(const double x, const double y, const double z) : Triplet(x, y, z){};
    ~Vector() = default;

    double length() const {
        return sqrt(lengthSquared());
    }

    double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    Vector normalize() const {
        double len = length();
        return Vector(x / len, y / len, z / len);
    }
};

// I'm not positive we want this to be this way, but it may be useful
inline bool operator==(const Vector& lhs, const Vector& rhs) {
    Vector normalizedLhs = lhs.normalize();
    Vector normalizedRhs = rhs.normalize();
    return normalizedLhs.getX() == normalizedRhs.getX() &&
           normalizedLhs.getY() == normalizedRhs.getY() &&
           normalizedLhs.getZ() == normalizedRhs.getZ();
}

inline double dot(const Vector& a, const Vector& b) {
    return a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ();
}

inline Vector cross(const Vector& a, const Vector& b) {
    return Vector(a.getY() * b.getZ() - a.getZ() * b.getY(), a.getZ() * b.getX() - a.getX() * b.getZ(), a.getX() * b.getY() - a.getY() * b.getX());
}

inline Vector normalize(const Vector& v) {
    return v.normalize();
}

#endif  // VECTOR_HPP
#include <cmath>

#include "triplet.hpp"
#include "utilities.hpp"

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

inline double length(const Vector& v) {
    return v.length();
}

inline Vector normalize(const Vector& v) {
    return v.normalize();
}

inline Vector reflect(const Vector& v, const Vector& n) {
    Vector vNorm = normalize(v);
    Vector nNorm = normalize(n);

    return vNorm - 2 * dot(vNorm, nNorm) * nNorm;
}

inline Vector refract(const Vector& uv, const Vector& n, const double etaiOverEtat) {
    Vector uvNorm = normalize(uv);
    Vector nNorm = normalize(n);

    double cosTheta = fmin(dot(-1 * uvNorm, nNorm), 1.0);
    Vector rOutPerp = etaiOverEtat * (uvNorm + cosTheta * nNorm);
    Vector rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * nNorm;
    return rOutPerp + rOutParallel;
}

inline static Vector randomVector() {
    return Vector(randomDouble(), randomDouble(), randomDouble());
}

inline static Vector randomVector(const double min, const double max) {
    return Vector(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline static Vector randomInUnitSphere() {
    while (true) {
        Vector p = randomVector(-1, 1);
        if (length(p) >= 1) {
            continue;
        }
        return p;
    }
}

inline static Vector randomInUnitDisk() {
    while (true) {
        Vector p = Vector(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (length(p) >= 1) {
            continue;
        }
        return p;
    }
}

inline static Vector randomUnitVector() {
    return normalize(randomInUnitSphere());
}

#endif  // VECTOR_HPP
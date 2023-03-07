#ifndef HIT_RECORD_HPP
#define HIT_RECORD_HPP

#include <cstdlib>

#include "color.hpp"
#include "material.hpp"
#include "point3d.hpp"
#include "vector.hpp"

struct HitRecord {
    Point3D point;
    std::shared_ptr<Material> material;
    Vector normal;
    double distanceFromOrigin;
    bool frontFace;

    inline void setFaceNormal(const Ray& ray, const Vector& outwardNormal) {
        frontFace = dot(ray.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : Vector(-1 * outwardNormal);
    }
};

#endif  // HIT_RECORD_HPP
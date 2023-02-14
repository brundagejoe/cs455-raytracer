#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "light.hpp"

struct HitRecord;

class Material {
   public:
    Material() = default;
    ~Material() = default;

    virtual Color getColor(const HitRecord& hitRecord, const Light& light, bool inShadow, const Ray& viewRay) const = 0;
};

#endif  // MATERIAL_HPP
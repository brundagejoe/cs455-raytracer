#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "hittable.hpp"
#include "light.hpp"

#define UNUSED(x) (void)(x)

struct HitRecord;

class Material {
   public:
    Material() = default;
    ~Material() = default;

    virtual Color getColor() const = 0;
    virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const = 0;
    virtual Color emission() const { return Color(0, 0, 0); }
};

#endif  // MATERIAL_HPP
#ifndef LAMBERTIAN_HPP
#define LAMBERTIAN_HPP

#include "hittable.hpp"
#include "light.hpp"
#include "material.hpp"
#include "ray.hpp"

class Lambertian : public Material {
   private:
    Color albedo;

   public:
    Lambertian() = default;
    Lambertian(Color albedo)
        : albedo(albedo) {}

    virtual ~Lambertian() = default;

    virtual Color getColor() const override { return albedo; }
    virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override {
        UNUSED(ray);
        Vector scatterDirection = hitRecord.normal + randomUnitVector();

        if (nearZero(scatterDirection)) {
            scatterDirection = hitRecord.normal;
        }

        attenuation = albedo;
        scatteredRay = Ray(hitRecord.point, scatterDirection);
        return true;
    }
};

#endif  // LAMBERTIAN_HPP
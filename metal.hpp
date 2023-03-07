#ifndef METAL_HPP
#define METAL_HPP

#include "hittable.hpp"
#include "light.hpp"
#include "material.hpp"
#include "ray.hpp"

class Metal : public Material {
   private:
    Color albedo;
    double fuzz;

   public:
    Metal() = default;
    Metal(Color albedo, double fuzz)
        : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual ~Metal() = default;

    virtual Color getColor() const override { return albedo; }
    virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override {
        Vector reflected = reflect(normalize(ray.getDirection()), normalize(hitRecord.normal));

        attenuation = albedo;
        scatteredRay = Ray(hitRecord.point, reflected + (randomInUnitSphere() * fuzz));
        return (dot(scatteredRay.getDirection(), hitRecord.normal) > 0);
    }
};

#endif  // METAL_HPP
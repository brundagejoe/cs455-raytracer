#ifndef DIELECTRIC_HPP
#define DIELECTRIC_HPP

#include "hittable.hpp"
#include "light.hpp"
#include "material.hpp"
#include "ray.hpp"

class Dielectric : public Material {
   private:
    double refractionIndex;

   public:
    Dielectric() = default;
    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    virtual ~Dielectric() = default;

    virtual Color getColor() const override { return Color(0, 0, 0); }
    virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractionRatio = hitRecord.frontFace ? (1.0 / refractionIndex) : refractionIndex;

        Vector unitDirection = normalize(ray.getDirection());
        double cosTheta = fmin(dot(-1 * unitDirection, hitRecord.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vector direction;

        if (cannotRefract) {
            direction = reflect(unitDirection, hitRecord.normal);
        } else {
            direction = refract(unitDirection, hitRecord.normal, refractionRatio);
        }

        // Vector refracted = refract(unitDirection, hitRecord.normal, refractionRatio);

        scatteredRay = Ray(hitRecord.point, direction);
        return true;
    }
};

#endif  // DIELECTRIC_HPP
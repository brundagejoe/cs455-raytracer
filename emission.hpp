#ifndef EMISSION_HPP
#define EMISSION_HPP

#include "color.hpp"
#include "material.hpp"

class Emission : public Material {
   private:
    Color intensity;

   public:
    Emission(double intensity = 1) {
        this->intensity = Color(intensity, intensity, intensity);
    }
    Emission(Color intensity) : intensity(intensity) {}
    virtual ~Emission() = default;

    Color getColor() const override { return Color(0, 0, 0); }
    bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override {
        UNUSED(ray);
        UNUSED(hitRecord);
        UNUSED(attenuation);
        UNUSED(scatteredRay);

        return false;
    }
    Color emission() const override { return intensity; }
};

#endif  // EMISSION_HPP
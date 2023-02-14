#ifndef PHONG_MATERIAL_HPP
#define PHONG_MATERIAL_HPP

#include "hittable.hpp"
#include "light.hpp"
#include "material.hpp"

class PhongMaterial : public Material {
   private:
    double specularCoefficient;
    double diffuseCoefficient;
    double ambientCoefficient;
    double shininess;

    Color diffuseColor;

   public:
    PhongMaterial() = default;
    PhongMaterial(Color diffuseColor, double specularCoefficient, double diffuseCoefficient, double ambientCoefficient, double shininess)
        : specularCoefficient(specularCoefficient), diffuseCoefficient(diffuseCoefficient), ambientCoefficient(ambientCoefficient), shininess(shininess), diffuseColor(diffuseColor) {}

    virtual ~PhongMaterial() = default;

    virtual Color getColor(const HitRecord& hitRecord, const Light& light, bool inShadow, const Ray& viewRay) const override;
};

Color PhongMaterial::getColor(const HitRecord& hitRecord, const Light& light, bool inShadow, const Ray& viewRay) const {
    double ambientIntensity = 0.1;

    double lightIntensity = inShadow ? 0 : light.getIntensity() / (light.getPosition() - hitRecord.point).lengthSquared();

    Vector L = normalize(light.getPosition() - hitRecord.point);
    Vector N = hitRecord.normal;
    Vector R = normalize(2 * dot(L, N) * N - L);
    Vector V = normalize(viewRay.getOrigin() - hitRecord.point);

    Vector color = ambientIntensity * ambientCoefficient * diffuseColor + lightIntensity * diffuseCoefficient * dot(L, N) * diffuseColor + lightIntensity * specularCoefficient * pow(dot(R, V), shininess) * light.getColor();
    return color;
}

#endif  // PHONG_MATERIAL_HPP
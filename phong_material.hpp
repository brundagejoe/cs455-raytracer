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
    double reflectance;

    Color diffuseColor;
    Color specularColor;

   public:
    PhongMaterial() = default;
    PhongMaterial(Color diffuseColor) : PhongMaterial(0.7, 0.1, 0.2, diffuseColor, Color(1, 1, 1), 32, 0) {}
    PhongMaterial(double diffuseCoefficient, double specularCoefficient, double ambientCoefficient, Color diffuseColor, Color specularColor, double shininess, double reflectance)
        : specularCoefficient(specularCoefficient), diffuseCoefficient(diffuseCoefficient), ambientCoefficient(ambientCoefficient), shininess(shininess), reflectance(reflectance), diffuseColor(diffuseColor), specularColor(specularColor) {}

    virtual ~PhongMaterial() = default;

    Color getColor(const HitRecord& hitRecord, const Light& light, bool inShadow, const Ray& viewRay) const;
    virtual Color getColor() const override { return diffuseColor; }
    virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Color& attenuation, Ray& scatteredRay) const override {
        UNUSED(ray);
        UNUSED(hitRecord);

        attenuation = diffuseColor;
        scatteredRay = Ray(hitRecord.point, hitRecord.normal + randomInUnitSphere());

        return true;
    }

    double getSpecularCoefficient() const { return specularCoefficient; }
    double getDiffuseCoefficient() const { return diffuseCoefficient; }
    double getAmbientCoefficient() const { return ambientCoefficient; }
    double getShininess() const { return shininess; }
    double getReflectance() const { return reflectance; }

    Color getSpecularColor() const { return specularColor; }
};

Color PhongMaterial::getColor(const HitRecord& hitRecord, const Light& light, bool inShadow, const Ray& viewRay) const {
    double ambientIntensity = 0.1;

    double lightIntensity = inShadow ? 0 : light.getIntensity();

    Vector L = normalize(light.getPosition() - hitRecord.point);
    Vector N = hitRecord.normal;
    Vector R = normalize(2 * dot(L, N) * N - L);
    Vector V = normalize(viewRay.getOrigin() - hitRecord.point);

    Vector color = ambientIntensity * ambientCoefficient * diffuseColor + lightIntensity * diffuseCoefficient * dot(L, N) * diffuseColor + lightIntensity * specularCoefficient * pow(dot(R, V), shininess) * specularColor;
    return color;
}

#endif  // PHONG_MATERIAL_HPP
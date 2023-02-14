#include <cmath>
#include <memory>

#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "phong_material.hpp"
#include "point3d.hpp"

#ifndef SPHERE_HPP
#define SPHERE_HPP

class Sphere : public Hittable {
   private:
    Point3D center;
    double radius;

   public:
    Sphere(const Point3D& center, double radius, std::shared_ptr<PhongMaterial> material = std::make_shared<PhongMaterial>(Color(255, 255, 255), 0.5, 0.5, 0.5, 10)) : Hittable(material), center(center), radius(radius) {}
    Sphere() = default;
    virtual ~Sphere() = default;

    Point3D getCenter() const { return center; }
    double getRadius() const { return radius; }

    bool hit(const Ray& ray, HitRecord& hitRecord) const override {
        double tMin = 0.001;

        Vector oc = ray.getOrigin() - center;
        double a = dot(ray.getDirection(), ray.getDirection());
        double b = 2 * dot(oc, ray.getDirection());
        double c = dot(oc, oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return false;
        }

        double root = (-b - sqrt(discriminant)) / (2 * a);

        if (root < tMin) {
            root = (-b + sqrt(discriminant)) / (2 * a);
            if (root < tMin) {
                return false;
            }
        }

        hitRecord.point = ray.at(root);
        hitRecord.normal = getNormal(hitRecord.point);
        hitRecord.distanceFromOrigin = root;
        return true;
    }

    Vector getNormal(const Point3D& p) const {
        return normalize(p - center);
    }
};

#endif  // SPHERE_HPP
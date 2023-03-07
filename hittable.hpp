#include "point3d.hpp"
#include "ray.hpp"

#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "color.hpp"
#include "hit_record.hpp"
#include "material.hpp"

class Hittable {
   private:
    std::shared_ptr<Material> material;

   public:
    Hittable() = default;
    Hittable(std::shared_ptr<Material> material) : material(material) {}
    ~Hittable() = default;

    void setMaterial(std::shared_ptr<Material> material) {
        this->material = material;
    }

    std::shared_ptr<Material> getMaterial() const {
        return material;
    }

    virtual bool hit(const Ray& ray, HitRecord& hitRecord) const = 0;
};

#endif  // HITTABLE_HPP
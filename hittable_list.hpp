#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"
#include "light.hpp"
#include "sphere.hpp"
#include "vector.hpp"

class HittableList : public Hittable {
   private:
    std::vector<std::shared_ptr<Hittable>> objects;
    Light light;

   public:
    HittableList() = default;

    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
    void addLight(Light light) { this->light = light; }

    virtual bool hit(const Ray& ray, HitRecord& hitRecord) const override;

    ~HittableList() = default;
};

bool HittableList::hit(const Ray& ray, HitRecord& hitRecord) const {
    bool hitAnything = false;
    double closestSoFar = INFINITY;
    for (const auto& object : objects) {
        if (object->hit(ray, hitRecord)) {
            if (hitRecord.distanceFromOrigin < closestSoFar) {
                closestSoFar = hitRecord.distanceFromOrigin;
                Ray shadowRay(hitRecord.point, light.getPosition() - hitRecord.point);
                HitRecord shadowHitRecord;
                bool shadowHit = false;
                for (const auto& object : objects) {
                    if (object->hit(shadowRay, shadowHitRecord)) {
                        shadowHit = true;
                        break;
                    }
                }

                hitRecord.color = object->getMaterial()->getColor(hitRecord, light, shadowHit, ray);
            }
            hitAnything = true;
        }
    }
    return hitAnything;
}

#endif  // HITTABLE_LIST_HPP
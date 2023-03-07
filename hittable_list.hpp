#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "color.hpp"
#include "hittable.hpp"
#include "light.hpp"
#include "sphere.hpp"
#include "vector.hpp"

class HittableList : public Hittable {
   private:
    std::vector<std::shared_ptr<Hittable>> objects;
    Light light;
    Color ambientLightColor;
    Color directionalLightColor;
    Vector directionalLightDirection;

   public:
    HittableList(Color ambientLightColor = Color(0, 0, 0), Color directionalLightColor = Color(1, 1, 1), Vector directionalLightDirection = Vector(0, 1, 0)) : ambientLightColor(ambientLightColor), directionalLightColor(directionalLightColor), directionalLightDirection(directionalLightDirection) {}

    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
    void addLight(Light light) { this->light = light; }
    void addAmbientLight(Color ambientLightColor) { this->ambientLightColor = ambientLightColor; }
    void addDirectionalLight(Color directionalLightColor, Vector directionalLightDirection) {
        this->directionalLightColor = directionalLightColor;
        this->directionalLightDirection = directionalLightDirection;
    }

    Light getLight() const { return light; }
    Color getAmbientLightColor() const { return ambientLightColor; }
    Color getDirectionalLightColor() const { return directionalLightColor; }
    Vector getDirectionalLightDirection() const { return directionalLightDirection; }

    virtual bool hit(const Ray& ray, HitRecord& hitRecord) const override;

    ~HittableList() = default;
};

bool HittableList::hit(const Ray& ray, HitRecord& hitRecord) const {
    bool hitAnything = false;
    double closestSoFar = INFINITY;
    HitRecord tempHitRecord;
    for (const auto& object : objects) {
        if (object->hit(ray, tempHitRecord)) {
            if (tempHitRecord.distanceFromOrigin < closestSoFar) {
                closestSoFar = tempHitRecord.distanceFromOrigin;
                hitRecord = tempHitRecord;
            }
            hitAnything = true;
        }
    }
    return hitAnything;
}

#endif  // HITTABLE_LIST_HPP
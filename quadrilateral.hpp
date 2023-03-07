#ifndef QUADRILATERAL_HPP
#define QUADRILATERAL_HPP

#include <cstdlib>

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "point3d.hpp"
#include "triangle.hpp"

class Quadrilateral : public Hittable {
   private:
    HittableList hittableList;

   public:
    Quadrilateral(const Point3D& a, const Point3D& b, const Point3D& c, const Point3D& d, std::shared_ptr<Material> material) : Hittable(material) {
        hittableList.add(std::make_shared<Triangle>(Triangle(a, b, c, getMaterial())));
        hittableList.add(std::make_shared<Triangle>(Triangle(a, c, d, getMaterial())));
    };
    virtual ~Quadrilateral() = default;

    virtual bool hit(const Ray& ray, HitRecord& hitRecord) const {
        return hittableList.hit(ray, hitRecord);
    };
};

#endif  // QUADRILATERAL_HPP
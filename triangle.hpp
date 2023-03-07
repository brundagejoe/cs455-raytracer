#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "hittable.hpp"

class Triangle : public Hittable {
   private:
    Point3D p0;
    Point3D p1;
    Point3D p2;

   public:
    Triangle(Point3D p0, Point3D p1, Point3D p2, std::shared_ptr<Material> material) : Hittable(material), p0(p0), p1(p1), p2(p2) {}
    Triangle() = default;
    virtual ~Triangle() = default;

    bool hit(const Ray& ray, HitRecord& hitRecord) const override;
};

bool Triangle::hit(const Ray& ray, HitRecord& hitRecord) const {
    // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm

    Vector edge1 = p1 - p0;
    Vector edge2 = p2 - p0;
    Vector h = cross(ray.getDirection(), edge2);
    double a = dot(edge1, h);

    if (a > -0.00001 && a < 0.00001) {
        return false;
    }

    double f = 1 / a;
    Vector s = ray.getOrigin() - p0;
    double u = f * dot(s, h);

    if (u < 0.0 || u > 1.0) {
        return false;
    }

    Vector q = cross(s, edge1);

    double v = f * dot(ray.getDirection(), q);

    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    double t = f * dot(edge2, q);

    if (t > 0.00001) {
        hitRecord.point = ray.at(t);
        hitRecord.setFaceNormal(ray, normalize(cross(edge1, edge2)));
        hitRecord.distanceFromOrigin = t;
        hitRecord.material = getMaterial();
        return true;
    }

    return false;
}

#endif  // TRIANGLE_HPP
#ifndef BOX_HPP
#define BOX_HPP

#include <cstdlib>

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "point3d.hpp"
#include "quadrilateral.hpp"
#include "vector.hpp"

class Box : public Hittable {
   private:
    HittableList hittableList;
    double rotationX;
    double rotationY;
    double rotationZ;

   public:
    Box(const Point3D& a, const Point3D& b, double rotationX, double rotationY, double rotationZ, std::shared_ptr<Material> material) : Hittable(material), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ) {
        double leftX = std::min(a.getX(), b.getX());
        double rightX = std::max(a.getX(), b.getX());
        double bottomY = std::min(a.getY(), b.getY());
        double topY = std::max(a.getY(), b.getY());
        double frontZ = std::max(a.getZ(), b.getZ());
        double backZ = std::min(a.getZ(), b.getZ());

        // Define the 8 corners of the box
        Point3D lowerLeftBack(leftX, bottomY, backZ);
        Point3D lowerRightBack(rightX, bottomY, backZ);
        Point3D upperLeftBack(leftX, topY, backZ);
        Point3D lowerRightFront(rightX, bottomY, frontZ);
        Point3D upperLeftFront(leftX, topY, frontZ);
        Point3D upperRightFront(rightX, topY, frontZ);
        Point3D upperRightBack(rightX, topY, backZ);
        Point3D lowerLeftFront(leftX, bottomY, frontZ);

        // Define the 6 faces of the box
        auto front = std::make_shared<Quadrilateral>(Quadrilateral(lowerLeftFront, lowerRightFront, upperRightFront, upperLeftFront, material));
        auto back = std::make_shared<Quadrilateral>(Quadrilateral(lowerLeftBack, upperLeftBack, upperRightBack, lowerRightBack, material));
        auto left = std::make_shared<Quadrilateral>(Quadrilateral(lowerLeftBack, lowerLeftFront, upperLeftFront, upperLeftBack, material));
        auto right = std::make_shared<Quadrilateral>(Quadrilateral(lowerRightBack, upperRightBack, upperRightFront, lowerRightFront, material));
        auto bottom = std::make_shared<Quadrilateral>(Quadrilateral(lowerLeftBack, lowerRightBack, lowerRightFront, lowerLeftFront, material));
        auto top = std::make_shared<Quadrilateral>(Quadrilateral(upperLeftBack, upperLeftFront, upperRightFront, upperRightBack, material));

        // Add the faces to a hittableList
        hittableList.add(front);
        hittableList.add(back);
        hittableList.add(left);
        hittableList.add(right);
        hittableList.add(bottom);
        hittableList.add(top);
    };

    Box(const Point3D& anchorPoint, double width, double height, double depth, double rotationX, double rotationY, double rotationZ, std::shared_ptr<Material> material) : Box(anchorPoint, Point3D(anchorPoint.getX() + width, anchorPoint.getY() + height, anchorPoint.getZ() + depth), rotationX, rotationY, rotationZ, material){};
    virtual ~Box() = default;

    virtual bool hit(const Ray& ray, HitRecord& hitRecord) const {
        // change the ray direction to the rotated direction
        Point3D rayDirection = ray.getDirection();
        Point3D rayOrigin = ray.getOrigin();
        Point3D rotatedRayDirection = rayDirection.rotateX(rotationX).rotateY(rotationY).rotateZ(rotationZ);
        Point3D rotatedRayOrigin = rayOrigin.rotateX(rotationX).rotateY(rotationY).rotateZ(rotationZ);
        Ray rotatedRay(rotatedRayOrigin, rotatedRayDirection);
        bool hit = hittableList.hit(rotatedRay, hitRecord);
        // adjust the normals to the original direction
        if (hit) {
            hitRecord.setFaceNormal(ray, Vector(Point3D(hitRecord.normal).rotateX(-rotationX).rotateY(-rotationY).rotateZ(-rotationZ)));
        }

        return hit;
    };
};

#endif  // BOX_HPP
#include <iostream>

#include "point3d.hpp"
#include "ray.hpp"
#include "vector.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
   private:
    Point3D lookFrom;
    Point3D lookAt;
    Vector vUp;
    double vFov;
    double aspectRatio;

    Point3D lowerLeftCorner;
    Vector horizontal;
    Vector vertical;

   public:
    Camera(Point3D lookFrom = Point3D(0, 0, 1), Point3D lookAt = Point3D(0, 0, 0), Vector vUp = Vector(0, 1, 0), double vFov = 90, double aspectRatio = 2) : lookFrom(lookFrom), lookAt(lookAt), vUp(vUp), vFov(vFov), aspectRatio(aspectRatio) {
        configureCamera();
    }

    void configureCamera() {
        double theta = vFov * M_PI / 180;
        double halfHeight = tan(theta / 2);
        double halfWidth = aspectRatio * halfHeight;

        Vector w = normalize(lookFrom - lookAt);
        Vector u = normalize(cross(vUp, w));
        Vector v = cross(w, u);

        lowerLeftCorner = static_cast<Vector>(lookFrom) - halfWidth * u - halfHeight * v - w;
        horizontal = 2 * halfWidth * u;
        vertical = 2 * halfHeight * v;
    }

    void setLookFrom(Point3D lookFrom) {
        this->lookFrom = lookFrom;
        configureCamera();
    }
    void setLookAt(Point3D lookAt) {
        this->lookAt = lookAt;
        configureCamera();
    }
    void setVUp(Vector vUp) {
        this->vUp = vUp;
        configureCamera();
    }
    void setVFov(double vFov) {
        this->vFov = vFov;
        configureCamera();
    }
    void setAspectRatio(double aspectRatio) {
        this->aspectRatio = aspectRatio;
        configureCamera();
    }

    Ray getRay(double u, double v) const {
        if (u < 0 || u > 1 || v < 0 || v > 1) {
            throw std::invalid_argument("u and v must be in range [0,1]");
        }
        return Ray(lookFrom, lowerLeftCorner + u * horizontal + v * vertical - static_cast<Vector>(lookFrom));
    }
};

#endif  // CAMERA_HPP
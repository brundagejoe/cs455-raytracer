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
    double aperature;

    Point3D lowerLeftCorner;
    Vector horizontal;
    Vector vertical;
    Vector u, v, w;
    double lensRadius;

   public:
    Camera(Point3D lookFrom = Point3D(0, 0, 1), Point3D lookAt = Point3D(0, 0, 0), Vector vUp = Vector(0, 1, 0), double vFov = 60, double aspectRatio = 2, double aperature = 0) : lookFrom(lookFrom), lookAt(lookAt), vUp(vUp), vFov(vFov), aspectRatio(aspectRatio), aperature(aperature) {
        configureCamera();
    }

    void configureCamera() {
        double theta = vFov * M_PI / 180;
        double halfHeight = tan(theta / 2);
        double halfWidth = aspectRatio * halfHeight;

        w = normalize(lookFrom - lookAt);
        u = normalize(cross(vUp, w));
        v = cross(w, u);

        double focusDistance = length(lookFrom - lookAt);

        horizontal = 2 * halfWidth * u * focusDistance;
        vertical = 2 * halfHeight * v * focusDistance;
        lowerLeftCorner = static_cast<Vector>(lookFrom) - horizontal / 2 - vertical / 2 - w * focusDistance;

        lensRadius = aperature / 2;
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

    void setAspectRatio(double aspectRatio) {
        this->aspectRatio = aspectRatio;
        configureCamera();
    }

    void setVFov(double vFov) {
        this->vFov = vFov;
        configureCamera();
    }

    void setAperature(double aperature) {
        this->aperature = aperature;
        configureCamera();
    }

    Ray getRay(double s, double t) const {
        if (s < 0 || s > 1 || t < 0 || t > 1) {
            throw std::invalid_argument("u and v must be in range [0,1]");
        }

        Vector randomDisk = lensRadius * randomInUnitDisk();
        Vector offset = u * randomDisk.getX() + v * randomDisk.getY();

        return Ray(lookFrom + offset, lowerLeftCorner + s * horizontal + t * vertical - static_cast<Vector>(lookFrom) - offset);
    }
};

#endif  // CAMERA_HPP
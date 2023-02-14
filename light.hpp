#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "color.hpp"
#include "point3d.hpp"

class Light {
   private:
    Point3D position;
    Color color;
    double intensity;

   public:
    Light() = default;
    Light(Point3D position, Color color, double intensity) : position(position), color(color), intensity(intensity) {}
    ~Light() = default;

    Point3D getPosition() const { return position; }
    Color getColor() const { return color; }
    double getIntensity() const { return intensity; }
};

#endif  // LIGHT_HPP
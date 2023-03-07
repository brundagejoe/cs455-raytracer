#include "color.hpp"

#include <iostream>

Color interpolateColor(const Color& a, const Color& b, const double t) {
    return a * (1 - t) + b * t;
}

std::ostream& operator<<(std::ostream& os, const Color& obj) {
    double floor = 0.0;
    double ceil = 255.0;

    double x = obj.getX();
    double y = obj.getY();
    double z = obj.getZ();

    // Consider removing this and just letting the values go out of range. That way we can clip later on
    x = std::max(floor, std::min(x, ceil));
    y = std::max(floor, std::min(y, ceil));
    z = std::max(floor, std::min(z, ceil));

    os << static_cast<int>(x) << " " << static_cast<int>(y) << " " << static_cast<int>(z);
    return os;
}
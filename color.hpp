#include <iostream>

#include "triplet.hpp"

#ifndef COLOR_HPP
#define COLOR_HPP

class Color : public Triplet {
   public:
    Color() = default;
    Color(const Triplet& t) : Triplet(t){};
    Color(const double x, const double y, const double z) : Triplet(x, y, z){};
    ~Color() = default;
};

std::ostream& operator<<(std::ostream& os, const Color& obj);

Color interpolateColor(const Color& a, const Color& b, const double t);

#endif  // COLOR_HPP
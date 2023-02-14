#include "triplet.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& os, const Triplet& obj) {
    os << obj.getX() << " " << obj.getY() << " " << obj.getZ();
    return os;
}

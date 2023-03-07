#include <cstdlib>

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

inline double randomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline int randomInt(int min, int max) {
    return min + static_cast<int>(randomDouble() * (max - min + 1));
}

inline double clip(double number, double min, double max) {
    if (number < min) {
        return min;
    } else if (number > max) {
        return max;
    } else {
        return number;
    }
}
#endif  // !UTILITIES_HPP
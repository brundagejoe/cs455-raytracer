#include <iostream>

#ifndef TRIPLET_HPP
#define TRIPLET_HPP

class Triplet {
   protected:
    double x;
    double y;
    double z;

   public:
    Triplet() = default;
    Triplet(const double x, const double y, const double z) : x(x), y(y), z(z){};
    ~Triplet() = default;

    Triplet& operator+=(const Triplet& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Triplet& operator+=(const double i) {
        x += i;
        y += i;
        z += i;
        return *this;
    }

    Triplet& operator++() {
        x++;
        y++;
        z++;
        return *this;
    }

    Triplet operator++(int) {
        Triplet tmp(*this);
        operator++();
        return tmp;
    }

    Triplet& operator-=(const Triplet& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Triplet& operator-=(const double i) {
        x -= i;
        y -= i;
        z -= i;
        return *this;
    }

    Triplet& operator--() {
        x--;
        y--;
        z--;
        return *this;
    }
    Triplet operator--(int) {
        Triplet tmp(*this);
        operator--();
        return tmp;
    }

    Triplet operator*=(const double i) {
        x *= i;
        y *= i;
        z *= i;
        return *this;
    }

    Triplet operator/=(const double i) {
        x /= i;
        y /= i;
        z /= i;
        return *this;
    }

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

std::ostream& operator<<(std::ostream& os, const Triplet& obj);

inline bool operator==(const Triplet& lhs, const Triplet& rhs) {
    return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ();
}

inline bool operator!=(const Triplet& lhs, const Triplet& rhs) { return !operator==(lhs, rhs); }

inline Triplet operator+(Triplet lhs, const Triplet& rhs) {
    lhs += rhs;
    return lhs;
}

inline Triplet operator+(Triplet lhs, const double rhs) {
    lhs += rhs;
    return lhs;
}

inline Triplet operator+(const double lhs, Triplet rhs) {
    rhs += lhs;
    return rhs;
}

inline Triplet operator-(Triplet lhs, const Triplet& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Triplet operator-(Triplet lhs, const double rhs) {
    lhs -= rhs;
    return lhs;
}

inline Triplet operator-(const double lhs, Triplet rhs) {
    rhs -= lhs;
    rhs *= -1;
    return rhs;
}

inline Triplet operator*(Triplet lhs, const double rhs) {
    lhs *= rhs;
    return lhs;
}

inline Triplet operator*(const double lhs, Triplet rhs) {
    rhs *= lhs;
    return rhs;
}

inline Triplet operator/(Triplet lhs, const double rhs) {
    lhs /= rhs;
    return lhs;
}

inline Triplet operator/(const double lhs, Triplet rhs) {
    return Triplet(lhs / rhs.getX(), lhs / rhs.getY(), lhs / rhs.getZ());
}

inline Triplet abs(const Triplet& t) {
    return Triplet(std::abs(t.getX()), std::abs(t.getY()), std::abs(t.getZ()));
}

#endif  // TRIPLET_HPP
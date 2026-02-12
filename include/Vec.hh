#include <cmath>
class Vec {
  public:
    double e[3]; // of form <x, y, z>

    Vec() : e{0, 0, 0} {}
    Vec(const double x, const double y, const double z) : e{x, y, z} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec operator+(const Vec& v) const {
        return Vec(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }
    Vec operator-(const Vec& v) const {
        return Vec(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }
    Vec operator*(const double t) const {
        return Vec(e[0] * t, e[1] * t, e[2] * t);
    }

    double dot(const Vec& v) const {
        return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
    }

    double mag() const { return std::sqrt(dot(*this)); }
    Vec unit_vector() { return *this * (1.0 / mag()); }
};

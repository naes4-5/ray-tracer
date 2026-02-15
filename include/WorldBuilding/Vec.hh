#pragma once
#include <cmath>

class Vec {
  public:
    double u, v, w; // <x, y, z>

    Vec() : u(0), v(0), w(0) {}
    Vec(const double x, const double y, const double z) : u(x), v(y), w(z) {}

    Vec operator+(const Vec& l) const { return Vec(u + l.u, v + l.v, w + l.w); }
    Vec operator-(const Vec& l) const { return Vec(u - l.u, v - l.v, w - l.w); }
    Vec operator*(const double t) const { return Vec(u * t, v * t, w * t); }
    Vec operator*(const Vec& l) {
        u *= l.u;
        v *= l.v;
        w *= l.w;
        return *this;
    }
    Vec operator/(const double t) const { return *this * (1.0 / t); }
    Vec& operator+=(const Vec& l) {
        this->u += l.u;
        this->v += l.v;
        this->w += l.w;
        return *this;
    };

    double dot(const Vec& l) const { return u * l.u + v * l.v + w * l.w; }

    double mag() const { return std::sqrt(dot(*this)); }
    Vec unit_vector() {
        auto magnitude{mag()};
        if (magnitude == 0)
            return Vec(0, 0, 0);
        return *this / magnitude;
    }
    Vec cross(const Vec& l) const {
        return Vec{
            v * l.w - w * l.v,
            w * l.u - u * l.w,
            u * l.v - v * l.u,
        };
    }
};

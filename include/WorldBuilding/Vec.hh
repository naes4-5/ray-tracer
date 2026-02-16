#pragma once

class Vec {
  public:
    double u, v, w; // <x, y, z>

    Vec();
    Vec(const double x, const double y, const double z);

    Vec operator+(const Vec& l) const;
    Vec operator+(const double l) const;
    Vec operator-(const Vec& l) const;
    Vec operator*(const double t) const;
    Vec operator*(const Vec& l);
    Vec operator/(const double t) const;
    Vec& operator+=(const Vec& l);

    double dot(const Vec& l) const;

    double mag() const;
    Vec unit_vector() const;
    Vec cross(const Vec& l) const;
};

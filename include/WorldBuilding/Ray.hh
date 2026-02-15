#pragma once
#include "Vec.hh"

class Ray {
  public:
    Vec orig;
    Vec dir;

    Ray() : orig(Vec{}), dir(Vec{0, 1, 0}) {}
    Ray(const Vec& origin, const Vec& direction)
        : orig(origin), dir(direction) {}

    Vec at(double t) const { return orig + (dir * t); }
};

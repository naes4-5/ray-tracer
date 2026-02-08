#pragma once
#include "Vec.h"

class Ray {
  public:
    Vec orig{};
    Vec dir{};

    Ray(const Vec& origin, const Vec& direction)
        : orig(origin), dir(direction) {}

    Vec at(double t) const { return orig + (dir * t); }
};

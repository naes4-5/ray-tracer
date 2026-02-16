#pragma once
#include "WorldBuilding/Vec.hh"

class Ray {
  public:
    Vec orig;
    Vec dir;

    Ray();
    Ray(const Vec& origin, const Vec& direction);

    Vec at(double t) const;
};

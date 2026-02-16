#include "WorldBuilding/Ray.hh"

Ray::Ray() : orig(Vec{}), dir(Vec{0, 1, 0}) {}
Ray::Ray(const Vec& origin, const Vec& direction)
    : orig(origin), dir(direction) {}

Vec Ray::at(double t) const { return orig + (dir * t); }

#pragma once
#include "Ray.hh"

struct hit_record {
    double t;
    Vec P;
    Vec N;
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const = 0;
};

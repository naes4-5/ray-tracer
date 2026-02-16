#pragma once
#include "WorldBuilding/Ray.hh"
#include <memory>

class Material;

struct hit_record {
    double t;
    Vec P;
    Vec N;
    std::shared_ptr<Material> mat_ptr;
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const = 0;
};

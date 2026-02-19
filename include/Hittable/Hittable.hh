#pragma once
#include "WorldBuilding/Ray.hh"
#include <memory>

class Material;

struct hit_record {
    std::shared_ptr<Material> mat_ptr;
    Vec P;
    Vec N; // outward
    double t;
    bool front_face;
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const = 0;
};

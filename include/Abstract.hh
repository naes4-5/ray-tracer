#pragma once
#include "Ray.hh"
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

class Material {
  public:
    virtual bool scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const = 0;
};

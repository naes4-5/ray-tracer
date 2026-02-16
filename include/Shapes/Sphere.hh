#pragma once
#include "Hittable/Hittable.hh"
#include <memory>

class Sphere : public Hittable {
  public:
    Vec center;
    double rad;
    std::shared_ptr<Material> mat_ptr;

    Sphere(const Vec c, double r, std::shared_ptr<Material> mat);

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override;
};

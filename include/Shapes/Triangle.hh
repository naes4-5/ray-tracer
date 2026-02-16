#pragma once
#include "Hittable/Hittable.hh"
#include "Shapes/Plane.hh"

class Triangle : public Hittable {
  public:
    Vec A, B, C;
    Vec N;
    Plane P;
    std::shared_ptr<Material> mat_ptr;

    Triangle(const Vec& a, const Vec& b, const Vec& c,
             std::shared_ptr<Material> mat);

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override;
};

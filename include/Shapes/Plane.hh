#pragma once
#include "Hittable/Hittable.hh"
#include <memory>

class Plane : public Hittable {
  public:
    Vec N; // normal vector
    Vec Q; // point on plane
    std::shared_ptr<Material> mat_ptr;

    Plane();
    Plane(const Vec& q);
    Plane(const Vec& q, const Vec& n, std::shared_ptr<Material> mat);

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override;
};

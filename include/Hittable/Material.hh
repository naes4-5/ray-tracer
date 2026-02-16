#pragma once
#include "Hittable/Hittable.hh"
#include "WorldBuilding/Ray.hh"

class Material {
  public:
    virtual bool scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const = 0;
};

#pragma once
#include "Hittable/Hittable.hh"
#include <cust_vector.hh>

class HittableList : public Hittable {
  public:
    cust_vector<Hittable*> objs;

    HittableList(cust_vector<Hittable*>& l);
    HittableList(std::initializer_list<Hittable*> l);

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override;
};

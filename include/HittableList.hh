#pragma once
#include "Hittable.hh"
#include <cust_vector.hh>

class HittableList : public Hittable {
  public:
    cust_vector<Hittable*> objs{};

    HittableList(cust_vector<Hittable*>& l) : objs(l) {}
    HittableList(std::initializer_list<Hittable*> l) {
        for (const auto& e : l) {
            objs.push_back(e);
        }
    }

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override {
        hit_record temp_rec{};
        bool hit_smth{};
        auto closest{t_max};
        for (const auto& o : objs) {
            if (o->hit(ray, t_min, closest, temp_rec)) {
                hit_smth = true;
                closest = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_smth;
    }
};

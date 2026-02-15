#pragma once
#include "Abstract.hh"
#include "util.hh"

class Matte : public Material {
  public:
    Vec color;

    Matte(const Vec& c) : color(c) {}

    static Vec rand_in_unit_sphere() {
        while (true) {
            Vec v{random_double(-1, 1), random_double(-1, 1),
                  random_double(-1, 1)};
            if (v.mag() >= 1)
                continue;
            return v;
        }
    }

    virtual bool scatter(const Ray& ray_in, hit_record& rec, Vec& attenuation,
                         Ray& scattered) const override {
        (void)ray_in;
        Vec dir{rec.N + rand_in_unit_sphere()};
        attenuation = color;
        scattered = Ray(rec.P, dir);
        return true;
    }
};

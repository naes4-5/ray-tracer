#pragma once
#include "Abstract.hh"
#include <memory>

class Plane : public Hittable {
  public:
    Vec N; // normal vector
    Vec Q; // point on plane
    std::shared_ptr<Material> mat_ptr;

    Plane() : N(0, 1, 0), Q(0, 0, 0) {}
    Plane(const Vec& q) : N(0, 1, 0), Q(q) {}
    Plane(const Vec& q, const Vec& n, std::shared_ptr<Material> mat)
        : N(n), Q(q), mat_ptr(mat) {}

    virtual bool hit(const Ray& ray, const double t_min, const double t_max,
                     hit_record& rec) const override {
        auto q_o{Q - ray.orig};
        auto denom{ray.dir.dot(N)};
        if (std::abs(denom) <= 1e-8)
            return false;
        auto soln{q_o.dot(N) / denom};
        if (soln < t_min || soln > t_max)
            return false;
        rec.t = soln;
        rec.P = ray.at(rec.t);
        rec.N = N;
        rec.mat_ptr = mat_ptr;
        return true;
    }
};
